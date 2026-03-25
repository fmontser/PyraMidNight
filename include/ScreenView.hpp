#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class ScreenView {
	public:

		ScreenView(sf::RenderWindow& window);
		virtual ~ScreenView();

		void Show();
		void Hide();
		void Draw();

	private:

		bool enabled;
		sf::RenderWindow& mWindow;
		std::vector<std::unique_ptr<sf::Drawable>> mDrawables;
};