#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "InputManager.hpp"


class ScreenView {
	public:
		virtual ~ScreenView() = default;

		void Show();
		void Hide();
		virtual void ProcessInput() = 0;

		const std::vector<std::shared_ptr<sf::Drawable>>&
		GetDrawables() const;

	protected:
		ScreenView();
		
		std::vector<std::shared_ptr<sf::Drawable>> mDrawables;

	private:

		bool enabled;
};