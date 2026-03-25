#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "ScreenView.hpp"

class RenderManager {
	public:
		RenderManager();
		void RenderFrame(ScreenView& screenView);

		sf::Time GetDeltaTime() const;
		sf::RenderWindow& GetWindow();

	private:
		sf::RenderWindow mWindow;
		sf::Clock        mClock;
		sf::Time         mDeltaTime;
};