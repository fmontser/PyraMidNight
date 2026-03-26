#pragma once
#include "ScreenView.hpp"
#include <string>

class TitleScreenView : public ScreenView {
	public:
		TitleScreenView();
		void ProcessInput(Game& game) override;

	private:
		std::shared_ptr<sf::Font> font;
		std::shared_ptr<sf::Text> titleTxt;
		std::shared_ptr<sf::Text> creditsTxt;
		std::shared_ptr<sf::Texture> backgroundTex;
		std::shared_ptr<sf::Sprite> background;

		std::string creditsStr;
};