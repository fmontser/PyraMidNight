#pragma once
#include "ScreenView.hpp"

class RoundScreenView : public ScreenView {
	public:
		RoundScreenView();
		void ProcessInput(Game& game) override;

	private:
		std::shared_ptr<sf::Font> font;
		std::shared_ptr<sf::Text> stubTxt;
		std::shared_ptr<sf::Texture> backgroundTex;
		std::shared_ptr<sf::Sprite> background;

		void UpdateCredits(Game& game);
};