//TODO check includes...
#include <optional>
#include <variant>
#include "InputManager.hpp"

namespace fknd {
	
	InputManager::InputManager(sf::RenderWindow &window) : mWindow(window) {
		mFrameInput = {};
	}
	
	InputManager::Input& InputManager::FetchInput() {
		ResetReleased();
		while (const auto event = mWindow.pollEvent()) {
			
			if (event->getIf<sf::Event::Closed>())
				mFrameInput.close = true;
	
			mFrameInput.holdLeft  = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);
			mFrameInput.holdRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);
	
			if (const auto* key = event->getIf<sf::Event::KeyReleased>()) {
				switch (key->code) {
					case sf::Keyboard::Key::A: mFrameInput.left = true; break;
					case sf::Keyboard::Key::D: mFrameInput.right = true; break;
					case sf::Keyboard::Key::W: mFrameInput.up = true; break;
					case sf::Keyboard::Key::S: mFrameInput.down = true; break;
					case sf::Keyboard::Key::Space: mFrameInput.action = true; break;
					case sf::Keyboard::Key::Num1: mFrameInput.coin = true; break;
					case sf::Keyboard::Key::Escape: mFrameInput.menu = true; break;
					default: break;
				}
			}
		}
		return mFrameInput;
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
