#include "PowerUp.hpp"

namespace pyramidnight {
	PowerUp::PowerUp(const sf::Texture& texture) : sf::Sprite(texture) {}
	
	void PowerUp::Spawn(
		const sf::Vector2f &position, std::vector<std::shared_ptr<sf::Drawable>>& drawables) {
		setPosition(position);
		drawables.push_back(shared_from_this());
	}

	void PowerUp::Update() {
		ApplyGravity();
	}

	void PowerUp::ApplyGravity() {
		//TODO implement
	}
}
