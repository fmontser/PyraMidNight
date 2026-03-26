#include "Bumper.hpp"
#include <algorithm>

Bumper::Bumper(const sf::Texture& texture) : sf::Sprite(texture) {
	mSpeed = 1000;
}

//TODO soften with lerp?
//TODO hardcoded values...
void Bumper::Move(int32_t magnitude, sf::Time& deltaTime) {
	sf::Vector2 position = this->getPosition();
	position.x += magnitude * mSpeed * deltaTime.asSeconds();
	position.x = std::clamp(position.x, 32.0f, (640.0f - 32.0f - 128.0f));
	this->setPosition(position);
}
