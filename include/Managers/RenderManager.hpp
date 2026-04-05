#pragma once
#include <SFML/Graphics.hpp>
#include "ScreenView.hpp"
#include "Common.hpp"

namespace pyramidnight {
	
	class RenderManager {
		public:
			RenderManager();
			void RenderFrame(
				std::vector<std::shared_ptr<sf::Drawable>>& drawables);
	
			sf::Time& GetDeltaTime();
			sf::RenderWindow& GetWindow();
	
		private:
			

			sf::RenderWindow mWindow;
			sf::Clock        mClock;
			sf::Time         mDeltaTime;
	};

}