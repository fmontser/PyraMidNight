#pragma once
#include "ScreenView.hpp"

class TitleScreenView : public ScreenView {
	public:
		TitleScreenView(sf::RenderWindow& window, sf::Time& deltaTime);

	private:
		std::shared_ptr<sf::RectangleShape> background;
};