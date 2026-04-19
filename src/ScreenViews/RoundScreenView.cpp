#include <algorithm>
#include <string>
#include <memory>
#include "RoundScreenView.hpp"
#include "Levels.hpp"
#include "AudioManager.hpp"
#include "ResourceManager.hpp"
#include "RenderManager.hpp"
#include "ScreenShake.hpp"
#include "ExtraScorePuP.hpp"
#include "ExtraCreditPuP.hpp"
#include "GhostPuP.hpp"
#include "MagicPuP.hpp"

namespace pyramidnight {

	RoundScreenView::RoundScreenView() : ScreenView() {
		mLvlIsLoaded = false;
		mIsLevelCompleted = false;
		mElapsedTimePenalty = 0.0f;
		mFont = ResourceManager::GetFont(PATH_FONT);

		mCreditsTxt = std::make_shared<sf::Text>(*mFont);
		mCreditsTxt->setString(std::string(ROUND_CREDITS_STR));
		mCreditsTxt->setCharacterSize(ROUND_TXT_CHAR_SZ);
		mCreditsTxt->setFillColor(ROUND_TXT_FILLCOL);
		mCreditsTxt->setOutlineColor(ROUND_TXT_OUTCOL);
		mCreditsTxt->setOutlineThickness(ROUND_TXT_OUTLINE_SZ);
		mCreditsTxt->setPosition({128.0f, 864.0f});

		mScoreTxt = std::make_shared<sf::Text>(*mFont);
		mScoreTxt->setString(std::string(ROUND_SCORE_STR));
		mScoreTxt->setCharacterSize(ROUND_TXT_CHAR_SZ);
		mScoreTxt->setFillColor(ROUND_TXT_FILLCOL);
		mScoreTxt->setOutlineColor(ROUND_TXT_OUTCOL);
		mScoreTxt->setOutlineThickness(ROUND_TXT_OUTLINE_SZ);
		mScoreTxt->setPosition({352.0f, 864.f});
		
		mScorePuPTex = ResourceManager::GetTexture(PATH_TEX_SCORE_PWRUP);
		mCreditPuPTex = ResourceManager::GetTexture(PATH_TEX_CREDIT_PWRUP);
		mGhostPuPTex = ResourceManager::GetTexture(PATH_TEX_GHOST_PWRUP);
		mMagicPuPTex = ResourceManager::GetTexture(PATH_TEX_MAGIC_PWRUP);

		mBackgroundTex = ResourceManager::GetTexture(PATH_TEX_BG);
		mBackground = std::make_shared<sf::Sprite>(sf::Sprite(*mBackgroundTex));
		mBackground->setColor(ROUND_BG_TINT);
		
		mWallTex = ResourceManager::GetTexture(PATH_TEX_WALL);
		mWallTex->setRepeated(true);
		mWallLeft = std::make_shared<Obstacle>(*mWallTex);
		mWallLeft->setTextureRect({{0, 0},{32, 896}});
		mWallLeft->setPosition({0, 32});
		mWallRight = std::make_shared<Obstacle>(*mWallTex);
		mWallRight->setTextureRect({{0, 0},{32, 896}});
		mWallRight->setPosition({608, 32});

		mCeilTex = ResourceManager::GetTexture(PATH_TEX_CEIL);
		mCeilTex->setRepeated(true);
		mCeil = std::make_shared<Obstacle>(*mCeilTex);
		mCeil->setTextureRect({{0, 0},{640, 32}});

		mBumperTex = std::make_shared<sf::Texture>(PATH_TEX_BUMP);
		mBumper = std::make_shared<Bumper>(*mBumperTex, *mMagicPuPTex);
		mBumper->setPosition({256, 832});
		
		mBallTex = ResourceManager::GetTexture(PATH_TEX_BALL);
		mBall = std::make_shared<Ball>(*mBallTex);
		
		mBlockTex = ResourceManager::GetTexture(PATH_TEX_BLOCK);
		
		mDeathArea = std::make_shared<sf::RectangleShape>(sf::RectangleShape({576.0f, 64.0f}));
		mDeathArea->setPosition({32, 864});
		mDeathArea->setFillColor(sf::Color::Transparent);

		mDrawables.push_back(mBackground);
		mDrawables.push_back(mCreditsTxt);
		mDrawables.push_back(mScoreTxt);
		mDrawables.push_back(mWallLeft);
		mDrawables.push_back(mWallRight);
		mDrawables.push_back(mCeil);
		mDrawables.push_back(mBumper);
		mDrawables.push_back(mBall);
		mDrawables.push_back(mDeathArea);

		mColdetVector.push_back(mCeil);
		mColdetVector.push_back(mWallLeft);
		mColdetVector.push_back(mWallRight);
		mColdetVector.push_back(mBumper);
		mColdetVector.push_back(mBall);
	}

	//TODO remove hardcoded 
	bool RoundScreenView::LoadLevel(const uint8_t& roundId) {
		auto& level = ROUNDS[roundId];
		const auto offset =sf::Vector2f(64,32);
		auto actualPos = sf::Vector2f(32,32);

		for (const auto& str : level) {
			for (const auto chara : str) {
				if (chara != '0') {
					auto block = std::make_shared<Block>(*mBlockTex, chara - '0');
					block->setPosition(actualPos);
					mDrawables.push_back(block);
					mColdetVector.push_back(block);
				}
				actualPos.x += offset.x;
			}
			actualPos.x = 32;
			actualPos.y += offset.y;
		}
		return true;
	}

	bool RoundScreenView::Update(const RoundScreenUpdate& update) {
 		if (!mLvlIsLoaded)
			mLvlIsLoaded = LoadLevel(update.roundId);
		if (UpdateGame(update))
			return false;
		return true;
	}

	bool RoundScreenView::UpdateGame(const RoundScreenUpdate& update) {

		for (const auto &collidable : mColdetVector) {
			if (collidable->IsDynamic) {
				for (const auto &collider : mColdetVector) {
					if (collidable != collider && collidable->CollidableType != collider->CollidableType) {
						ICollidable::Info info = collidable->OnCollision(*collider);
						if (info.valueMod != 0)
							ProcessInteractions(update, info, collidable);
						if (info.collisionPoint != std::nullopt)
							break;
					}
				}
			}
		}

		if (UpdateBall(update.action, update.deltaTime) == Ball::State::DEAD)
			LoseBall(update) ;
		UpdateBumper(update);
		UpdatePowerUps(update.credits, update.score, update.deltaTime);
		//UpdateMisiles(update.deltaTime);
		CleanObjectVectors();
		UpdateTexts(update);
		ScoreTimePenalty(update.score, update.deltaTime);
		CheckWinLoseConditions();
		return mIsLevelCompleted;
	}

	void RoundScreenView::UpdateBumper(const RoundScreenUpdate& update) {
		Bumper::BumperUpdate bumperUpdate {
			update.holdLeft,
			update.holdRight,
			update.action,
			update.fine,
			update.coarse,
			update.deltaTime,
			mDrawables,
			mMisileVector
		};
		mBumper->Update(bumperUpdate);
	}
	
	Ball::State RoundScreenView::UpdateBall(bool action, const sf::Time &deltaTime) {
		Ball::UpdateBall update {
			action,
			mBumper->getPosition(),
			deltaTime,
			*mDeathArea
		};
		return mBall->Update(update);
	}

	void RoundScreenView::UpdatePowerUps(uint8_t& credits, uint32_t& score, const sf::Time &deltaTime) {
		(void)score;
		(void)credits;

		for (const auto &obj : mColdetVector) {
			if (obj->CollidableType != ICollidable::Type::POWER_UP)
				continue ;
			auto& pup = static_cast<PowerUp&>(*obj);
			pup.Update(deltaTime);
		}
	}

	void RoundScreenView::ProcessInteractions(const RoundScreenUpdate& update, 
		const ICollidable::Info& info, std::shared_ptr<ICollidable> collidable) {

		switch (collidable->CollidableType) {
			case ICollidable::Type::POWER_UP: ProcessPowerUpInteraction(update, info, collidable); break;
			case ICollidable::Type::BLOCK: ProcessBlockInteraction(update, info, collidable); break;
			default: break;
		}
	}

	void RoundScreenView::ProcessPowerUpInteraction(const RoundScreenUpdate& update, 
		const ICollidable::Info& info, std::shared_ptr<ICollidable> collidable) {

		auto pup = std::static_pointer_cast<PowerUp>(collidable);
		if (info.valueMod != 0) {
			switch (pup->PowerUpType) {
				case PowerUp::Type::SCORE: AddScore(update.score, info.valueMod); break;
				case PowerUp::Type::CREDIT: AddCredit(update.credits); break;
				case PowerUp::Type::GHOST: /*mBumper->SetSpeedPenalty(info.valueMod); */break;
				case PowerUp::Type::MAGIC: /*mBumper->EnableMagic(info.valueMod);*/ break;
				default: break;
			}
		}
		if (info.destroyed)
			mDestroyedSprites.push_back(pup);
	}

	void RoundScreenView::ProcessBlockInteraction(const RoundScreenUpdate& update, 
		const ICollidable::Info& info, std::shared_ptr<ICollidable> collidable) {

		auto block = std::static_pointer_cast<Block>(collidable);
		if (info.destroyed) {
			AddScore(update.score, info.valueMod);
			GeneratePowerUp(info);
			mDestroyedSprites.push_back(block);
		}
	}

	void RoundScreenView::UpdateMisiles(const sf::Time &deltaTime) {
		for (const auto& obj : mMisileVector) {
			for (const auto& pup : mPowerUpVector) {
				if (pup->PowerUpType == PowerUp::Type::GHOST) {
					auto& ghost = static_cast<GhostPuP&>(*pup);
					ICollidable::Info info = obj->OnCollision(ghost);
					obj->Update(deltaTime);

					if (info.destroyed) {
						mDestroyedSprites.push_back(std::dynamic_pointer_cast<sf::Sprite>(obj));
					}

					if (info.valueMod != 0) {
						switch (obj->MisileType) {
							case Misile::Type::HOLY_MISILE: ghost.Defeat(); break;
							default: break;
						}
					}
					break;
				}
			}
		}
	}
	
	void RoundScreenView::CheckWinLoseConditions() {
		auto it = std::find_if(mColdetVector.begin(), mColdetVector.end(),
		[](const std::shared_ptr<ICollidable> collidable){
			return collidable->CollidableType == ICollidable::Type::BLOCK;
		});
		if (it == mColdetVector.end())
			mIsLevelCompleted = true;

		if (mIsLevelCompleted) {
			auto sb = ResourceManager::GetAudio(PATH_AUD_NEXTROUND);
			AudioManager::Play({sb,VOL_AUD_NEXTROUND, PolySound::Type::SFX, false});
		}
	}

	void RoundScreenView::CleanObjectVectors() {
		for (const auto& sprite : mDestroyedSprites) {

			auto powerUp = std::dynamic_pointer_cast<PowerUp>(sprite);
			auto itPowerUp = std::find(mPowerUpVector.begin(), mPowerUpVector.end(), powerUp);
			if (itPowerUp != mPowerUpVector.end())
				mPowerUpVector.erase(itPowerUp);

			auto misile = std::dynamic_pointer_cast<Misile>(sprite);
			auto itMisile = std::find(mMisileVector.begin(), mMisileVector.end(), misile);
			if (itMisile != mMisileVector.end())
				mMisileVector.erase(itMisile);

			auto collidable = std::dynamic_pointer_cast<ICollidable>(sprite);
			auto itColdet = std::find(mColdetVector.begin(), mColdetVector.end(), collidable);
			if (itColdet != mColdetVector.end())
				mColdetVector.erase(itColdet);

			auto itDrawable = std::find(mDrawables.begin(), mDrawables.end(), sprite);
			if (itDrawable != mDrawables.end())
				mDrawables.erase(itDrawable);
		}
		mDestroyedSprites.clear();
	}

	void RoundScreenView::UpdateTexts(const RoundScreenUpdate &update) {
		mCreditsTxt->setString(std::string(ROUND_CREDITS_STR)
			.append(std::to_string(update.credits)));
		mScoreTxt->setString(std::string(ROUND_SCORE_STR)
			.append(std::to_string(update.score)));
	}

	// lose 1 point per second
	void RoundScreenView::ScoreTimePenalty(uint32_t &score, sf::Time& deltaTime) {
		mElapsedTimePenalty += deltaTime.asSeconds();
		if (mElapsedTimePenalty >= 1.0f) {
			AddScore(score, SCORE_TIME_PENALTY);
			mElapsedTimePenalty -= 1.0f;
		}
	}

	void RoundScreenView::LoseBall(const RoundScreenUpdate &update) {
		ConsumeCredit(update.credits);
		AddScore(update.score, SCORE_LOSE_BALL_PENALTY);
		if (update.credits == 0) {
			auto sb = ResourceManager::GetAudio(PATH_AUD_GAMEOVER);
			AudioManager::Play({sb,VOL_AUD_GAMEOVER, PolySound::Type::SFX, false});
			mIsLevelCompleted = true;
		}
		RenderManager::DisplayEffect(std::make_unique<ScreenShake>(EFF_SHAKE_LOSEBALL_TIME, EFF_SHAKE_LOSEBALL_POWER));
		auto sb = ResourceManager::GetAudio(PATH_AUD_BALL_LOSE);
		AudioManager::Play({sb, VOL_AUD_BALL_LOSE, PolySound::Type::SFX, false});
		mDestroyedSprites.push_back(mBall);
		ReplaceBall();
	};

	void RoundScreenView::ReplaceBall() {
		mBall = std::make_shared<Ball>(*mBallTex);
		mDrawables.push_back(mBall);
		mColdetVector.push_back(mBall);
	}

	void RoundScreenView::AddScore(uint32_t& score, int32_t points) {
		int64_t score64 = static_cast<int64_t>(score);
		int64_t points64 = static_cast<int64_t>(points);
		int64_t maxScore64 = static_cast<int64_t>(GAME_MAX_SCORE);

 		if (points64 < 0 && score64 < std::abs(points64))
			score = 0;
		else if (points64 > (maxScore64 - score64))
			score = maxScore64;
		else
			score += points64;
	}

	void RoundScreenView::ConsumeCredit(uint8_t& credits) {
		if (credits > 0)
			credits--;
	}

	void RoundScreenView::AddCredit(uint8_t& credits) {
		if (credits < GAME_MAX_CREDITS)
			credits++;
	}

	std::optional<std::shared_ptr<PowerUp>> RoundScreenView::GeneratePowerUp(ICollidable::Info info) {
		if (info.type != ICollidable::Type::BLOCK)
			return std::nullopt;
	
		auto spawnType = mSpawner.RollSpawn();
		std::shared_ptr<PowerUp> spawn = nullptr;

		if (spawnType == std::nullopt)
			return std::nullopt;
		
		switch (*spawnType) {
			case PowerUp::Type::SCORE: spawn = std::make_shared<ExtraScorePuP>(*mScorePuPTex, SCORE_PWRUP_POINTS); break;
			case PowerUp::Type::CREDIT: spawn = std::make_shared<ExtraCreditPuP>(*mCreditPuPTex); break;
			case PowerUp::Type::GHOST: spawn = std::make_shared<GhostPuP>(*mGhostPuPTex); break;
			case PowerUp::Type::MAGIC: spawn = std::make_shared<MagicPuP>(*mMagicPuPTex); break;
			default: break;
		}
		if (spawn != nullptr) {
			spawn->Spawn(*info.collisionPoint, mDrawables);
			mColdetVector.push_back(spawn);
			return spawn;
		}
		return std::nullopt;
	}


	void RoundScreenView::Log(const std::string &msg) {
		(void)msg;
		//TODO log system
	}

}