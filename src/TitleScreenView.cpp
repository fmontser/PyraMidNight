#include "TitleScreenView.hpp"
#include <filesystem>

#include <iostream>

//TODO hardcoded values
TitleScreenView::TitleScreenView() : ScreenView() {
	backgroundTex = std::make_shared<sf::Texture>(sf::Texture("assets/Background.png"));
	background = std::make_shared<sf::Sprite>(sf::Sprite(*backgroundTex));
	mDrawables.push_back(background);
}

void TitleScreenView::ProcessInput() {
	//TODO
}