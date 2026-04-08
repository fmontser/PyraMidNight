#include <SFML/Main.hpp>
#include <iostream>
#include <stdexcept>
#include "ResourceManager.hpp"
#include "UserDataManager.hpp"
#include "RenderManager.hpp"
#include "AudioManager.hpp"
#include "InputManager.hpp"
#include "Game.hpp"
#include "Common.hpp"

int main(int argc, char* argv[]) {
	int testLevel = -1;
	int finalLevel = pyramidnight::GAME_FINAL_ROUND_ID;

	if (argc > 2) {
		std::cerr << "Error: Wrong number of arguments\n";
		return 1;
	}
	if (argc == 2) {
		try {
			testLevel = std::stoi(argv[1]);
			if (testLevel > finalLevel || testLevel < 0)
				throw std::runtime_error("");
		} catch (...) {
			std::cerr << "Error: Argument must be a positive number in range of (0 - "
				<< finalLevel << ")\n";
			return 1;
		}
	}

	pyramidnight::UserDataManager::Init();
	pyramidnight::ResourceManager::Init();
	pyramidnight::RenderManager::Init();
	pyramidnight::InputManager::Init();
	pyramidnight::AudioManager::Init();
	pyramidnight::Game game;
	game.Run(testLevel);
	return (0);
}