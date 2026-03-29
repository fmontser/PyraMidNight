#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Common.hpp"

namespace fknd {
	
	class Game;
	
	class ScreenView {
		public:
			virtual ~ScreenView() = default;
	
			virtual bool Update(Game& game) = 0;
	
			std::vector<std::shared_ptr<sf::Drawable>>&
			GetDrawables();
	
		protected:
			ScreenView();
			
			std::vector<std::shared_ptr<sf::Drawable>> mDrawables;
	};

}