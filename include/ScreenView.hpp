#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class Game;

class ScreenView {
	public:
		virtual ~ScreenView() = default;

		virtual void ProcessInput(Game& game) = 0;

		std::vector<std::shared_ptr<sf::Drawable>>&
		GetDrawables();

	protected:
		ScreenView();
		
		std::vector<std::shared_ptr<sf::Drawable>> mDrawables;
};