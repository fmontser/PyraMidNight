#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class ScreenView {
	public:
		virtual ~ScreenView() = default;

		void Show();
		void Hide();

		const std::vector<std::shared_ptr<sf::Drawable>>&
		GetDrawables() const;

	protected:
		ScreenView();
		
		std::vector<std::shared_ptr<sf::Drawable>> mDrawables;

	private:

		bool              enabled;
		//TODO
/* 		sf::RenderWindow& mWindow;
		sf::Time&         mDeltaTime; */
};