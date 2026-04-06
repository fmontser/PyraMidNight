#include <SFML/Main.hpp>
#include "ResourceManager.hpp"
#include "UserDataManager.hpp"
#include "RenderManager.hpp"
#include "AudioManager.hpp"
#include "InputManager.hpp"
#include "Game.hpp"

int main(int argc, char* argv[]) {
	(void)argc;
	(void)argv;

	pyramidnight::UserDataManager::Init();
	pyramidnight::ResourceManager::Init();
	pyramidnight::RenderManager::Init();
	//pyramidnight::InputManager::Init(); //TODO disable comment
	pyramidnight::AudioManager::Init();
	pyramidnight::Game game;
	game.Run();
	return (0);
}