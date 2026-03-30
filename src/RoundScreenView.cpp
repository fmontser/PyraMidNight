#include <cmath>
#include <algorithm>
#include "RoundScreenView.hpp"
#include "Levels.hpp"

namespace fknd {

	RoundScreenView::RoundScreenView() : ScreenView() {

		mLvlIsLoaded = false;
		//TODO filesystem exception control
		mFont = std::make_shared<sf::Font>(PATH_FONT);

		mCreditsTxt = std::make_shared<sf::Text>(*mFont);
		mCreditsTxt->setString(std::string(ROUND_CREDITS_STR));
		mCreditsTxt->setCharacterSize(ROUND_TXT_CHAR_SZ);
		mCreditsTxt->setFillColor(ROUND_TXT_FILLCOL);
		mCreditsTxt->setOutlineColor(ROUND_TXT_OUTCOL);
		mCreditsTxt->setOutlineThickness(1);
		mCreditsTxt->setPosition({128.0f, 864.0f});

		mScoreTxt = std::make_shared<sf::Text>(*mFont);
		mScoreTxt->setString(std::string(ROUND_SCORE_STR));
		mScoreTxt->setCharacterSize(ROUND_TXT_CHAR_SZ);
		mScoreTxt->setFillColor(ROUND_TXT_FILLCOL);
		mScoreTxt->setOutlineColor(ROUND_TXT_OUTCOL);
		mScoreTxt->setOutlineThickness(ROUND_TXT_OUTLINE_SZ);
		mScoreTxt->setPosition({352.0f, 864.f});
		
		mBackgroundTex = std::make_shared<sf::Texture>(sf::Texture(PATH_TEX_BG));
		mBackground = std::make_shared<sf::Sprite>(sf::Sprite(*mBackgroundTex));
		mBackground->setColor(ROUND_BG_TINT);
		
		mWallTex = std::make_shared<sf::Texture>(sf::Texture(PATH_TEX_WALL));
		mWallTex->setRepeated(true);
		mWallLeft = std::make_shared<sf::Sprite>(sf::Sprite(*mWallTex));
		mWallLeft->setTextureRect({{0, 0},{32, 896}});
		mWallLeft->setPosition({0, 32});
		mWallRight = std::make_shared<sf::Sprite>(sf::Sprite(*mWallTex));
		mWallRight->setTextureRect({{0, 0},{32, 896}});
		mWallRight->setPosition({608, 32});

		mCeilTex = std::make_shared<sf::Texture>(sf::Texture(PATH_TEX_CEIL));
		mCeilTex->setRepeated(true);
		mCeil = std::make_shared<sf::Sprite>(*mCeilTex);
		mCeil->setTextureRect({{0, 0},{640, 32}});

		mBumperTex = std::make_shared<sf::Texture>(PATH_TEX_BUMP);
		mBumper = std::make_shared<Bumper>(*mBumperTex);
		mBumper->setPosition({256, 832});
		
		mBallTex = std::make_shared<sf::Texture>(PATH_TEX_BALL);
		mBall = std::make_shared<Ball>(*mBallTex);

		mBlockTex = std::make_shared<sf::Texture>(PATH_TEX_BLOCK);

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

	bool RoundScreenView::Update(RoundScreenUpdate update) {
 		if (!mLvlIsLoaded)
			mLvlIsLoaded = LoadLevel(update.roundId);
		if (update.action)
			mBall->Launch();
		if (update.holdLeft)
			mBumper->Move(-1, update.deltaTime);
		else if (update.holdRight)
			mBumper->Move(1, update.deltaTime);

		UpdateBall(update.deltaTime);
		UpdateBlocks();
		UpdateCredits(update.credits);
		UpdateScore(update.score);
		if (!UpdateGame(update.credits))
			return false;
		return true;
	}

	bool RoundScreenView::LoadLevel(uint8_t& roundId) {
		auto& level = ROUNDS[roundId];
		const auto offset =sf::Vector2f(64,32);
		auto actualPos = sf::Vector2f(32,32);

		for (const auto& str : level) {
			for (const auto chara : str) {
				if (chara != '0') {
					auto block = std::make_shared<Block>(*mBlockTex, 1); //TODO set block variants when available
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

	void RoundScreenView::UpdateBall(const sf::Time &deltaTime)
	{
		if (mBall->GetState() == Ball::State::PLAYING) {
			for (const auto &obj : mColdetVector) {
				float distance = GetBallDistance(*obj);

				if (distance <= mBall->GetRadius()) {
					mBall->Bounce(*obj, distance);
					if (typeid(*obj) == typeid(Block)) {
						if (dynamic_cast<Block*>(obj.get())->Damage())
							mDestroyedSprites.push_back(obj);
					} else if (typeid(*obj) == typeid(Bumper)) {
						mBall->ApplyBumperMod(*obj);
					}
					break;
				}
			}
		}
		mBall->Update(mBumper->getPosition(), deltaTime);
	}


	void RoundScreenView::UpdateBlocks() {
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

	bool RoundScreenView::UpdateGame(uint8_t& credits) {
		//Lose
		if (mDeathArea->getGlobalBounds().contains(mBall->getPosition())) {
			return LoseBall(credits);;
		}
		//Win
		if (mBlockVector.empty())
			return false;
		return true;
	}

	void RoundScreenView::UpdateCredits(uint8_t& credits) {
		mCreditsTxt->setString(std::string(ROUND_CREDITS_STR)
			.append(std::to_string(credits)));
	}

	void RoundScreenView::UpdateScore(uint32_t& score) {
		//TODO delete score test
		AddScore(score, 1);

		mScoreTxt->setString(std::string(ROUND_SCORE_STR)
			.append(std::to_string(score)));
	}

	bool RoundScreenView::LoseBall(uint8_t& credits) {
		ConsumeCredit(credits);
		//TODO score penalty?
		if (credits == 0) {
			return false;
		}
		mBall->ResetPos(mBumper->getPosition());
		return true;
	};

	float RoundScreenView::GetBallDistance(const sf::Sprite& obj) {
		auto bPos = mBall->getPosition();
		auto rect = obj.getGlobalBounds();
		float closestX = std::clamp(bPos.x, rect.position.x, rect.position.x + rect.size.x);
		float closestY = std::clamp(bPos.y, rect.position.y, rect.position.y + rect.size.y);
		float distX = bPos.x - closestX;
		float distY = bPos.y - closestY;
		return std::sqrtf((distX * distX) + (distY * distY));
	}

	void RoundScreenView::AddScore(uint32_t& score, uint32_t points) {
		if (points > (GAME_MAX_SCORE - score))
			score = GAME_MAX_SCORE;
		else
			score += points;
	}

	void RoundScreenView::ConsumeCredit(uint8_t& credits) {
		if (credits > 0)
			credits--;
	}
	
	bool RoundScreenView::Update() { return false; }
}