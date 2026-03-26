#pragma once
#include "ScreenView.hpp"
#include "Round.hpp"

class RoundScreenView : public ScreenView {
	public:
		RoundScreenView();
		void ProcessInput(Game& game) override;

	private:
		std::shared_ptr<sf::Font> font;
		std::shared_ptr<sf::Text> creditsTxt;
		std::shared_ptr<sf::Text> scoreTxt;
		std::shared_ptr<sf::Texture> backgroundTex;
		std::shared_ptr<sf::Sprite> background;

		std::shared_ptr<sf::Texture> wallTex;
		std::shared_ptr<sf::Sprite> wallLeft;
		std::shared_ptr<sf::Sprite> wallRight;

		std::shared_ptr<sf::Texture> ceilTex;
		std::shared_ptr<sf::Sprite> ceil;

		std::unique_ptr<Round> round;

		void UpdateCredits(Game& game);
		void UpdateScore(Game &game);
};