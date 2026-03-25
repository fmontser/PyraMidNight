#include "TitleScreenView.hpp"

//TODO hardcoded values
TitleScreenView::TitleScreenView() : ScreenView() {
	background = std::make_shared<sf::RectangleShape>(
		sf::RectangleShape(sf::Vector2f(640.0f, 896.0f)));

	//TODO delete color test
	background->setFillColor(sf::Color::Green);

	mDrawables.push_back(background);
}