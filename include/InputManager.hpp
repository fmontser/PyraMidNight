#pragma once
#include <SFML/Graphics.hpp>

class InputManager {
	public:
		struct Input {
			bool up;
			bool down;
			bool left;
			bool right;
			bool action;
			bool coin;
			bool menu;
			bool close;
		};

		InputManager(sf::RenderWindow& window);

		Input& FetchInput();

	private:
		void ResetInput();
		
		sf::RenderWindow& mWindow;
		Input             mFrameInput;
};