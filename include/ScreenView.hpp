#pragma once
#include <SFML/Graphics.hpp>

class ScreenView {
	public:

		ScreenView(sf::RenderWindow& window);
		virtual ~ScreenView();

		void Show();
		void Hide();

	private:
		sf::RenderWindow& mWindow;
};