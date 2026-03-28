#pragma once
#include "ScreenView.hpp"
#include <string>

class EndScreenView : public ScreenView {
	public:
		EndScreenView();
		void Update(Game& game) override;

	private:
		std::shared_ptr<sf::Font> mFont;
		std::shared_ptr<sf::Text> mTitleTxt;
		std::shared_ptr<sf::Text> mCreditsTxt;
		std::shared_ptr<sf::Text> mStartTxt;
		std::shared_ptr<sf::Texture> mBackgroundTex;
		std::shared_ptr<sf::Sprite> mBackground;

		std::vector<std::shared_ptr<sf::Text>> mRanking;
};