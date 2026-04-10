#include "PowerUp.hpp"

namespace pyramidnight {
	PowerUp::PowerUp(const sf::Texture& texture) : sf::Sprite(texture) {}
	
	void PowerUp::Spawn(const sf::Vector2f &position) {
		(void)position;
		//TODO implement
	}

	void PowerUp::ApplyGravity() {
		//TODO implement
	}
}
