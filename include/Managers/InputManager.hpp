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
	
			static void Init();
			static Input& FetchInput(sf::RenderWindow& window);
			
		private:
			Input             mFrameInput;
			
			InputManager();
			InputManager(const InputManager& src) =  delete;
			InputManager& operator=(const InputManager& src) = delete;

			static InputManager& instance() {
				static InputManager inst;
				return inst;
			}

			void ResetReleased();
			
	};

}