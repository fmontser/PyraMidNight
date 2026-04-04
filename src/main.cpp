#include <SFML/Main.hpp>
#include "Game.hpp"
#include "UserDataManager.hpp"

//TODO move init here
/* #include "ResourceManager.hpp"
#include "InputManager.hpp"
#include "RenderManager.hpp" */

int main(int argc, char* argv[]) {
	(void)argc;
	(void)argv;

	pyramidnight::UserDataManager::Init();

	pyramidnight::Game game;
	game.Run();
	return (0);
}