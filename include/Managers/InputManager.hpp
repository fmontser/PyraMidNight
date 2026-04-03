#pragma once
#include <SFML/Graphics.hpp>
#include "Common.hpp"

namespace pyramidnight {
	
	class InputManager {
		public:
			struct Input {
				bool left;
				bool right;
				bool up;
				bool down;
				bool holdLeft;
				bool holdRight;
				bool coarse;
				bool fine;
				bool action;
				bool coin;
				bool menu;
				bool close;
			};
	
			InputManager(sf::RenderWindow& window);
	
			const Input& FetchInput();
	
		private:
			void ResetReleased();
			
			sf::RenderWindow& mWindow;
			Input             mFrameInput;
	};

}