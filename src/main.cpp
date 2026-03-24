//TODO revisar includes
#include <SFML/Graphics.hpp>
#include "Game.hpp"

//TODO to class
void fetchInput(sf::RenderWindow& window) {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			window.close();
	}
}

//TODO to class
void drawFrame(sf::RenderWindow& window) {
	window.clear(sf::Color::Black);
	window.display();
}

int main() {
	//TODO remove hardcoded values
	//TODO library health checks
	sf::RenderWindow window(sf::VideoMode(640, 896), "FranKanoid");

	//TODO clase time?
	sf::Clock clock;

	
	Game game;

	// Main loop
	while (window.isOpen()) {
		sf::Time deltaTime = clock.restart();

		game.Update();
		fetchInput(window);
		drawFrame(window);
	}
	return (0);
}