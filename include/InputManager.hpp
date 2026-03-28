#pragma once
#include <SFML/Graphics.hpp>

class InputManager {
	public:
		struct Input {
			bool up;
			bool down;
			bool left;
			bool holdLeft;
			bool right;
			bool holdRight;
			bool action;
			bool coin;
			bool menu;
			bool close;
		};

		InputManager(sf::RenderWindow& window);

		Input& FetchInput();

	private:
		void ResetReleased();
		
		sf::RenderWindow& mWindow;
		Input             mFrameInput;
};