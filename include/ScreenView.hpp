#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Common.hpp"

namespace fknd {
	
	//TODO delete forward on refactor
	class Game;

	class ScreenView {
		public:
			virtual ~ScreenView() = default;

			virtual bool Update() = 0;
	
			std::vector<std::shared_ptr<sf::Drawable>>&
			GetDrawables();
	
		protected:
			ScreenView();
			
			std::vector<std::shared_ptr<sf::Drawable>> mDrawables;
	};

}