#pragma once
#include "ScreenView.hpp"

class TitleScreenView : public ScreenView {
	public:
		TitleScreenView();

	private:
		std::shared_ptr<sf::RectangleShape> background;
};