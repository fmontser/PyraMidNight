#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include "Common.hpp"

namespace pyramidnight {
	
	class ScreenView {
		public:
			std::vector<std::shared_ptr<sf::Drawable>>& GetDrawables();
			virtual ~ScreenView() = default;
		
		protected:
			std::vector<std::shared_ptr<sf::Drawable>> mDrawables;
		};

}