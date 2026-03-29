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
				sf::Time& deltaTime;
				bool      holdLeft;
				bool      holdRight;
				bool      action;
				uint8_t&  credits;
				uint32_t& score;
			};

			RoundScreenView();

			bool Update(RoundScreenUpdate update);

		private:
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
			


			void LoadLevel(const std::array<const std::string, LVL_DIMENSIONS2>& level);
			void UpdateBall(const sf::Time &deltaTime);
			void UpdateBlocks();
			bool UpdateGame(uint8_t& credits);
			void UpdateCredits(uint8_t& credits);
			void UpdateScore(uint32_t& score);
			bool LoseBall(uint8_t& credits);
			float GetBallDistance(const sf::Sprite &obj);
			void AddScore(uint32_t& score, uint32_t points);
			void ConsumeCredit(uint8_t& credits);
			bool Update();
	};

}