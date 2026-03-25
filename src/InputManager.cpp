#include <optional>
#include <variant>
#include "InputManager.hpp"

InputManager::InputManager(sf::RenderWindow &window) : mWindow(window) {
	mFrameInput = {};
}

InputManager::Input& InputManager::FetchInput() {
	ResetInput();

	while (const auto event = mWindow.pollEvent()) {
		
		if (event->getIf<sf::Event::Closed>())
			mFrameInput.close = true;

		if (const auto* key = event->getIf<sf::Event::KeyReleased>()) {
			switch (key->code) {
				case sf::Keyboard::Key::W: mFrameInput.up = false; break;
				case sf::Keyboard::Key::S: mFrameInput.down = false; break;
				case sf::Keyboard::Key::A: mFrameInput.left = false; break;
				case sf::Keyboard::Key::D: mFrameInput.right = false; break;
				case sf::Keyboard::Key::Space: mFrameInput.action = false; break;
				case sf::Keyboard::Key::Num1: mFrameInput.coin = false; break;
				case sf::Keyboard::Key::Escape: mFrameInput.menu = false; break;
				default: break;
			}
		}
	}
	return mFrameInput;
}

void InputManager::ResetInput() { mFrameInput = {};}
