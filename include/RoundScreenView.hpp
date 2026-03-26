#pragma once
#include "ScreenView.hpp"
#include "Round.hpp"

class RoundScreenView : public ScreenView {
	public:
		RoundScreenView();
		void ProcessInput(Game& game) override;

	private:
		std::shared_ptr<sf::Font> mFont;
		std::shared_ptr<sf::Text> mCreditsTxt;
		std::shared_ptr<sf::Text> mScoreTxt;
		std::shared_ptr<sf::Texture> mBackgroundTex;
		std::shared_ptr<sf::Sprite> mBackground;

		std::shared_ptr<sf::Texture> mWallTex;
		std::shared_ptr<sf::Sprite> mWallLeft;
		std::shared_ptr<sf::Sprite> mWallRight;

		std::shared_ptr<sf::Texture> mCeilTex;
		std::shared_ptr<sf::Sprite> mCeil;

		std::unique_ptr<Round> mRound;

		void UpdateCredits(Game& game);
		void UpdateScore(Game &game);
};