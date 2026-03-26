#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class Game;

class ScreenView {
	public:
		virtual ~ScreenView() = default;

		virtual void ProcessInput(Game& game) = 0;

		const std::vector<std::shared_ptr<sf::Drawable>>&
		GetDrawables() const;

	protected:
		ScreenView();
		
		std::vector<std::shared_ptr<sf::Drawable>> mDrawables;
};