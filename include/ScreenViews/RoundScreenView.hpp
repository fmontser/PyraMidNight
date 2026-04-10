#pragma once
#include "ICollidable.hpp"
#include "ScreenView.hpp"
#include "Obstacle.hpp"
#include "Bumper.hpp"
#include "Ball.hpp"
#include "Block.hpp"
#include "Common.hpp"
#include "Spawner.hpp"
#include "PowerUp.hpp"

namespace pyramidnight {

	class RoundScreenView : public ScreenView {
		public:
			struct RoundScreenUpdate {
				uint8_t&          roundId;
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

			bool Update(const RoundScreenUpdate& update);

		private:
			bool                         mLvlIsLoaded;
			float                        mElapsedTimePenalty;
			std::shared_ptr<sf::Font>    mFont;
			std::shared_ptr<sf::Text>    mCreditsTxt;
			std::shared_ptr<sf::Text>    mScoreTxt;
			std::shared_ptr<sf::Texture> mBackgroundTex;
			std::shared_ptr<sf::Sprite>  mBackground;
			
			std::shared_ptr<sf::Texture> mWallTex;
			std::shared_ptr<Obstacle>    mWallLeft;
			std::shared_ptr<Obstacle>    mWallRight;
			std::shared_ptr<sf::Texture> mCeilTex;
			std::shared_ptr<Obstacle>    mCeil;
			
			std::shared_ptr<sf::Texture> mBumperTex;
			std::shared_ptr<Bumper>      mBumper;
			std::shared_ptr<sf::Texture> mBallTex;
			std::shared_ptr<Ball>        mBall;
			std::shared_ptr<sf::Texture> mBlockTex;
			
			std::shared_ptr<sf::RectangleShape>       mDeathArea;
			std::vector<std::shared_ptr<ICollidable>> mColdetVector;
			std::vector<std::shared_ptr<Block>>       mBlockVector;
			std::vector<std::shared_ptr<PowerUp>>     mPowerUpVector;
			std::vector<std::shared_ptr<sf::Sprite>>  mDestroyedSprites;
			Spawner                                   mSpawner;

			bool LoadLevel(const uint8_t& roundId);
			void UpdateSpawnables(uint32_t &score, const sf::Time &deltaTime);
			void UpdateBall(uint32_t &score, const sf::Time &deltaTime);
			void UpdateBlocks();
			bool UpdateGame(const RoundScreenUpdate &update);
			void UpdateTexts(const RoundScreenUpdate &update);
			void ScoreTimePenalty(uint32_t &score, sf::Time &deltaTime);
			bool LoseBall(const RoundScreenUpdate &update);
			void AddScore(uint32_t& score, int32_t points);
			void ConsumeCredit(uint8_t& credits);
			std::optional<std::shared_ptr<PowerUp>> GeneratePowerUp(ICollidable::Info info);
			void Log(const std::string &msg) override;

	};

}