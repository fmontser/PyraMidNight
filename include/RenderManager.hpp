#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "ScreenView.hpp"
#include "Common.hpp"

namespace fknd {
	
	class RenderManager {
		public:
			RenderManager();
			void RenderFrame(ScreenView& screenView);
	
			sf::Time& GetDeltaTime();
			sf::RenderWindow& GetWindow();
	
		private:
			sf::RenderWindow mWindow;
			sf::Clock        mClock;
			sf::Time         mDeltaTime;
	};

}