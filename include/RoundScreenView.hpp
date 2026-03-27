#pragma once
#include "ScreenView.hpp"
#include "Bumper.hpp"
#include "Ball.hpp"
#include "Block.hpp"

class RoundScreenView : public ScreenView {
	public:
		RoundScreenView();
		void Update(Game &game) override;

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
		
		void LoadLevel(const std::array<const std::string, 9>& level);
		void UpdateBall(const sf::Time& deltaTime);
		void UpdateBlocks();
		void UpdateCredits(Game& game);
		void UpdateScore(Game &game);
		float GetBallDistance(const sf::Sprite &obj);
};