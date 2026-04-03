#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Common.hpp"

namespace pyramidnight {
	
	class ScreenView {
		public:
			virtual bool Update() = 0;
			std::vector<std::shared_ptr<sf::Drawable>>& GetDrawables();

			void Pause();
			void Resume();
			
		protected:
			ScreenView() = default;
			
			sf::Clock mClock;
			std::vector<std::shared_ptr<sf::Drawable>> mDrawables;
		};

}