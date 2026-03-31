#pragma once
#include "ScreenView.hpp"
#include "Bumper.hpp"
#include "Ball.hpp"
#include "Block.hpp"
#include "Common.hpp"

namespace fknd {

	class RoundScreenView : public ScreenView {
		public:
			struct RoundScreenUpdate {
				uint8_t&          roundId;
				sf::RenderWindow& window;
				sf::Time&         deltaTime;
				bool              holdLeft;
				bool              holdRight;
				bool              coarse;
				bool              fine;
				bool              action;
				uint8_t&          credits;
				uint32_t&         score;
			};

			RoundScreenView();

			bool Update(RoundScreenUpdate update);

		private:
			bool         mLvlIsLoaded;
			bool         mShaking;
			float        mShaketime;
			sf::Vector2f mShakeOldCenter;

			std::shared_ptr<sf::Font>    mFont;
			std::shared_ptr<sf::Text>    mCreditsTxt;
			std::shared_ptr<sf::Text>    mScoreTxt;
			std::shared_ptr<sf::Texture> mBackgroundTex;
			std::shared_ptr<sf::Sprite>  mBackground;
			
			std::shared_ptr<sf::Texture> mWallTex;
			std::shared_ptr<sf::Sprite>  mWallLeft;
			std::shared_ptr<sf::Sprite>  mWallRight;
			std::shared_ptr<sf::Texture> mCeilTex;
			std::shared_ptr<sf::Sprite>  mCeil;
			
			std::shared_ptr<sf::Texture> mBumperTex;
			std::shared_ptr<Bumper>      mBumper;
			std::shared_ptr<sf::Texture> mBallTex;
			std::shared_ptr<Ball>        mBall;
			std::shared_ptr<sf::Texture> mBlockTex;
			
			std::shared_ptr<sf::RectangleShape>      mDeathArea;
			std::vector<std::shared_ptr<sf::Sprite>> mColdetVector;
			std::vector<std::shared_ptr<Block>>      mBlockVector;
			std::vector<std::shared_ptr<sf::Sprite>> mDestroyedSprites;

			bool LoadLevel(uint8_t& roundId);
			void UpdateBall(uint32_t& score, const sf::Time& deltaTime);
			void UpdateBlocks(sf::Time& deltaTime);
			bool UpdateGame(uint32_t& score, uint8_t& credits);
			void UpdateCredits(uint8_t& credits);
			void UpdateScore(uint32_t& score);
			void ScoreTimePenalty(uint32_t& score);
			bool LoseBall(uint32_t& score, uint8_t& credits);
			float GetBallDistance(const sf::Sprite& obj);
			void AddScore(uint32_t& score, int32_t points);
			void ConsumeCredit(uint8_t& credits);
			void ScreenShake(sf::RenderWindow &window, sf::Time &deltaTime, float &mShakeTime);
			bool Update();
	};

}