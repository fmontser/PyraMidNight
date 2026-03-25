#pragma once
#include "ScreenView.hpp"

class TitleScreenView : public ScreenView {
	public:
		TitleScreenView();
		void ProcessInput() override;

	private:
		std::shared_ptr<sf::RectangleShape> background;
};