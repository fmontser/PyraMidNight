#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Common.hpp"

namespace fknd {
	
	class ScreenView {
		public:
			struct ScreenUpdate {};

			virtual bool Update() = 0;
			std::vector<std::shared_ptr<sf::Drawable>>& GetDrawables();

			
		protected:
			ScreenView();
			
			std::vector<std::shared_ptr<sf::Drawable>> mDrawables;
		};

}