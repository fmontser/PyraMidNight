#include "Round.hpp"
#include "RoundScreenView.hpp"

Round::Round(RoundScreenView& screenView) : 
	mScreenView(screenView) {
	auto& drawables = mScreenView.GetDrawables();
	
	mPlayArea = std::make_shared<sf::RectangleShape>(sf::RectangleShape({576.0f, 864.0f}));
	mPlayArea->setPosition({32,32});
	mPlayArea->setFillColor(sf::Color::Green);
	drawables.push_back(mPlayArea);
}
