#include "InputManager.hpp"
#include "RenderManager.hpp"

namespace pyramidnight {
	
	InputManager::InputManager() {
		mFrameInput = {};
	}

	void InputManager::Init() { instance(); }

	InputManager::Input &InputManager::FetchInput(sf::RenderWindow& window) {
		auto& frameInput = instance().mFrameInput;

		instance().ResetReleased();
		while (const auto event = window.pollEvent()) {
			if (event->getIf<sf::Event::Closed>())
				window.close();

			// holding key inputs
			frameInput.holdLeft  = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);
			frameInput.holdRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);
			frameInput.coarse  = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift);
			frameInput.fine = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RControl);
	
			// release key inputs
			if (const auto* key = event->getIf<sf::Event::KeyReleased>()) {
				switch (key->code) {
					case sf::Keyboard::Key::A: frameInput.left = true; break;
					case sf::Keyboard::Key::D: frameInput.right = true; break;
					case sf::Keyboard::Key::W: frameInput.up = true; break;
					case sf::Keyboard::Key::S: frameInput.down = true; break;
					case sf::Keyboard::Key::Space: frameInput.action = true; break;
					case sf::Keyboard::Key::Num1: frameInput.coin = true; break;
					case sf::Keyboard::Key::Escape: frameInput.menu = true; break;
					default: break;
				}
			}
		}
		return frameInput;
	}

	void InputManager::ResetReleased() { 
		mFrameInput.up = false;
		mFrameInput.down = false;
		mFrameInput.left = false;
		mFrameInput.right = false;
		mFrameInput.action = false;
		mFrameInput.coin = false;
		mFrameInput.menu = false;
	}

}
