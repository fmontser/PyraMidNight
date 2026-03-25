#include "InputManager.hpp"

InputManager::InputManager(sf::RenderWindow &window) : mWindow(window) {
	mFrameInput = {};
}

//TODO check to simplify trigger events
InputManager::Input& InputManager::FetchInput() {
	sf::Event event;
	
	ResetInput();
	while (mWindow.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			mFrameInput.close = true;

		switch (event.key.code) {
			case sf::Keyboard::W: mFrameInput.up = (event.type == sf::Event::KeyPressed); break;
			case sf::Keyboard::S: mFrameInput.down = (event.type == sf::Event::KeyPressed); break;
			case sf::Keyboard::A: mFrameInput.left = (event.type == sf::Event::KeyPressed); break;
			case sf::Keyboard::D: mFrameInput.right = (event.type == sf::Event::KeyPressed); break;
			case sf::Keyboard::Space:  mFrameInput.action = (event.type == sf::Event::KeyPressed); break;
			case sf::Keyboard::Num1:   mFrameInput.coin = (event.type == sf::Event::KeyPressed); break;
			case sf::Keyboard::Escape: mFrameInput.menu = (event.type == sf::Event::KeyPressed); break;
			default: break;
		}
	}
	return mFrameInput;
}

void InputManager::ResetInput() { mFrameInput = {};}
