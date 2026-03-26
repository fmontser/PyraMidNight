#pragma once
#include "ScreenView.hpp"
#include <string>

class TitleScreenView : public ScreenView {
	public:
		TitleScreenView();
		void Update(Game& game) override;

	private:
		std::shared_ptr<sf::Font> font;
		std::shared_ptr<sf::Text> titleTxt;
		std::shared_ptr<sf::Text> creditsTxt;
		std::shared_ptr<sf::Text> startTxt;
		std::shared_ptr<sf::Texture> mBackgroundTex;
		std::shared_ptr<sf::Sprite> mBackground;

		std::string creditsStr;

		void UpdateCredits(Game& game);
};