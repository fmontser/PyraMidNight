#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class ScreenView {
	public:
		virtual ~ScreenView() = default;

		void Show();
		void Hide();
		//TODO not doing IOC...
		void Draw();

	protected:
		ScreenView(sf::RenderWindow& window, sf::Time& deltaTime);
		
		std::vector<std::shared_ptr<sf::Drawable>> mDrawables;

	private:

		bool              enabled;
		sf::RenderWindow& mWindow;
		sf::Time&         mDeltaTime;
};