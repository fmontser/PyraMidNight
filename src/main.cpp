#include <SFML/Main.hpp>
#include "Game.hpp"

int main(int argc, char* argv[]) {
	(void)argc;
	(void)argv;
	pyramidnight::Game game;
	game.Run();
	return (0);
}