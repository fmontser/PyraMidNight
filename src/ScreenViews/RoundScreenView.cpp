#include <algorithm>
#include <string>
#include <memory>
#include "RoundScreenView.hpp"
#include "Levels.hpp"
#include "AudioManager.hpp"
#include "ResourceManager.hpp"
#include "RenderManager.hpp"
#include "ScreenShake.hpp"

namespace pyramidnight {

	RoundScreenView::RoundScreenView() : ScreenView() {
		mLvlIsLoaded = false;
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
		
		mBackgroundTex = ResourceManager::GetTexture(PATH_TEX_BG);
		mBackground = std::make_shared<sf::Sprite>(sf::Sprite(*mBackgroundTex));
		mBackground->setColor(ROUND_BG_TINT);
		
		mWallTex = ResourceManager::GetTexture(PATH_TEX_WALL);
		mWallTex->setRepeated(true);
		mWallLeft = std::make_shared<sf::Sprite>(sf::Sprite(*mWallTex));
		mWallLeft->setTextureRect({{0, 0},{32, 896}});
		mWallLeft->setPosition({0, 32});
		mWallRight = std::make_shared<sf::Sprite>(sf::Sprite(*mWallTex));
		mWallRight->setTextureRect({{0, 0},{32, 896}});
		mWallRight->setPosition({608, 32});

		mCeilTex = ResourceManager::GetTexture(PATH_TEX_CEIL);
		mCeilTex->setRepeated(true);
		mCeil = std::make_shared<sf::Sprite>(*mCeilTex);
		mCeil->setTextureRect({{0, 0},{640, 32}});

		mBumperTex = std::make_shared<sf::Texture>(PATH_TEX_BUMP);
		mBumper = std::make_shared<Bumper>(*mBumperTex);
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
	}

	bool RoundScreenView::Update(const RoundScreenUpdate& update) {
 		if (!mLvlIsLoaded)
			mLvlIsLoaded = LoadLevel(update.roundId);
		if (update.action)
			mBall->Launch();
		if (update.holdLeft)
			mBumper->Move(-1, update.deltaTime, update.fine, update.coarse);
		else if (update.holdRight)
			mBumper->Move(1, update.deltaTime, update.fine, update.coarse);
		if (!UpdateGame(update))
			return false;
		return true;
	}

	bool RoundScreenView::LoadLevel(const uint8_t& roundId) {
		auto& level = ROUNDS[roundId];
		const auto offset =sf::Vector2f(64,32);
		auto actualPos = sf::Vector2f(32,32);

		for (const auto& str : level) {
			for (const auto chara : str) {
				if (chara != '0') {
					auto block = std::make_shared<Block>(*mBlockTex, chara - '0');
					block->setPosition(actualPos);
					mBlockVector.push_back(block);
				}
				actualPos.x += offset.x;
			}
			actualPos.x = 32;
			actualPos.y += offset.y;
		}

		for (const auto& block : mBlockVector) {
			mDrawables.push_back(block);
			mColdetVector.push_back(block);
		}
		return true;
	}

	//TODO remove smelly code, make objects ICollidable
	void RoundScreenView::UpdateBall(uint32_t& score, const sf::Time &deltaTime)
	{
		if (mBall->GetState() == Ball::State::PLAYING) {
			for (const auto &obj : mColdetVector) {
				float distance = mBall->GetBallDistance(*obj);

				if (distance <= mBall->GetRadius()) {
					mBall->Bounce(*obj, distance);
					if (typeid(*obj) == typeid(Block)) {
						auto* block = dynamic_cast<Block*>(obj.get());
						if (block->Damage()) {
							AddScore(score, block->GetScore());
							mDestroyedSprites.push_back(obj);
						}
					} else if (typeid(*obj) == typeid(Bumper)) {
						mBall->ApplyBumperMod(*obj);
					}
					break;
				}
			}
		}
		mBall->Update(mBumper->getPosition(), deltaTime);
	}


	void RoundScreenView::UpdateBlocks(const sf::Time& deltaTime) {
		for (auto& block : mBlockVector) {
			block->Update(deltaTime);
		}

		for (const auto& sprt : mDestroyedSprites) {
			auto itBlock = std::find(mBlockVector.begin(), mBlockVector.end(), sprt);
			if (itBlock != mBlockVector.end())
				mBlockVector.erase(itBlock);

			auto itColdet = std::find(mColdetVector.begin(), mColdetVector.end(), sprt);
			if (itColdet != mColdetVector.end())
				mColdetVector.erase(itColdet);

			auto itDrawable = std::find(mDrawables.begin(), mDrawables.end(), sprt);
			if (itDrawable != mDrawables.end())
				mDrawables.erase(itDrawable);
		}
		mDestroyedSprites.clear();
	}

	bool RoundScreenView::UpdateGame(const RoundScreenUpdate& update) {
		UpdateBall(update.score, update.deltaTime);
		UpdateBlocks(update.deltaTime);
		UpdateTexts(update);
		ScoreTimePenalty(update.score, update.deltaTime);

		//Lose
		if (mDeathArea->getGlobalBounds().contains(mBall->getPosition())) {
			return LoseBall(update);;
		}
		//Win
		if (mBlockVector.empty()) {
			auto sb = ResourceManager::GetAudio(PATH_AUD_NEXTROUND);
			AudioManager::Play({sb,VOL_AUD_NEXTROUND, PolySound::Type::SFX, false});
			return false;
		}
		return true;
	}

	void RoundScreenView::UpdateTexts(const RoundScreenUpdate &update) {
		mCreditsTxt->setString(std::string(ROUND_CREDITS_STR)
			.append(std::to_string(update.credits)));
		mScoreTxt->setString(std::string(ROUND_SCORE_STR)
			.append(std::to_string(update.score)));
	}

	void RoundScreenView::ScoreTimePenalty(uint32_t &score, sf::Time& deltaTime) {
		mElapsedTimePenalty += deltaTime.asSeconds();
		if (mElapsedTimePenalty >= 1.0f) {
			AddScore(score, SCORE_TIME_PENALTY);
			mElapsedTimePenalty -= 1.0f;
		}
	}

	bool RoundScreenView::LoseBall(const RoundScreenUpdate &update) {
		ConsumeCredit(update.credits);
		AddScore(update.score, SCORE_LOSE_BALL);
		if (update.credits == 0) {
			auto sb = ResourceManager::GetAudio(PATH_AUD_GAMEOVER);
			AudioManager::Play({sb,VOL_AUD_GAMEOVER, PolySound::Type::SFX, false});
			return false;
		}
		mBall->ResetPos(mBumper->getPosition());
		RenderManager::DisplayEffect(std::make_unique<ScreenShake>(EFF_SHAKE_LOSEBALL_TIME, EFF_SHAKE_LOSEBALL_POWER));
		auto sb = ResourceManager::GetAudio(PATH_AUD_BALL_LOSE);
		AudioManager::Play({sb, VOL_AUD_BALL_LOSE, PolySound::Type::SFX, false});
		return true;
	};

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

	void RoundScreenView::Log(const std::string &msg) {
		(void)msg;
		//TODO log system
	}

}