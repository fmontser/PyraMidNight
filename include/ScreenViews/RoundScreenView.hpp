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
#include "Misile.hpp"

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
			bool                         mIsLevelCompleted;
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
			std::shared_ptr<sf::Texture> mScorePuPTex;
			std::shared_ptr<sf::Texture> mCreditPuPTex;
			std::shared_ptr<sf::Texture> mGhostPuPTex;
			std::shared_ptr<sf::Texture> mMagicPuPTex;
			
			std::shared_ptr<sf::RectangleShape>       mDeathArea;
			std::vector<std::shared_ptr<ICollidable>> mColdetVector;
			std::vector<std::shared_ptr<sf::Sprite>>  mDestroyedSprites;
			Spawner                                   mSpawner;

			bool LoadLevel(const uint8_t& roundId);
			bool UpdateGame(const RoundScreenUpdate &update);
			Ball::State UpdateBall(bool action, const sf::Time &deltaTime);
			void UpdateBumper(const RoundScreenUpdate &update);
			void UpdatePowerUps(const sf::Time &deltaTime);
			
			void ProcessInteractions(const RoundScreenUpdate &update,
				const ICollidable::Info &info, std::shared_ptr<ICollidable> collidable);
				
			void ProcessPowerUpInteraction(const RoundScreenUpdate &update,
				const ICollidable::Info &info, std::shared_ptr<ICollidable> collidable);

			void ProcessMisileInteraction(const RoundScreenUpdate &update,
				const ICollidable::Info &info, std::shared_ptr<ICollidable> collidable);

			void ProcessBlockInteraction(const RoundScreenUpdate &update,
				const ICollidable::Info &info, std::shared_ptr<ICollidable> collidable);
				
			void UpdateMisiles(const sf::Time &deltaTime);
			void CheckWinLoseConditions();
			void CleanObjectVectors();
			void UpdateTexts(const RoundScreenUpdate &update);
			void ScoreTimePenalty(uint32_t &score, sf::Time &deltaTime);
			void LoseBall(const RoundScreenUpdate &update);
			void ReplaceBall();
			void AddScore(uint32_t &score, int32_t points);
			void ConsumeCredit(uint8_t& credits);
			void AddCredit(uint8_t &credits);
			std::optional<std::shared_ptr<PowerUp>> GeneratePowerUp(ICollidable::Info info);
			void Log(const std::string &msg) override;

	};

}