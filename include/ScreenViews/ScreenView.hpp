#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Common.hpp"

namespace pyramidnight {
	
	class ScreenView {
		public:
			virtual bool Update() = 0;
			std::vector<std::shared_ptr<sf::Drawable>>& GetDrawables();
			
		protected:
			ScreenView() = default;

			std::vector<std::shared_ptr<sf::Drawable>> mDrawables;
		};

}