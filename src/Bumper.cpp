#include <algorithm>
#include "Bumper.hpp"

Bumper::Bumper(const sf::Texture& texture) : sf::Sprite(texture) {
	mSpeed = 0.45f;
}

//TODO soften with lerp?
//TODO hardcoded values...
void Bumper::Move(int8_t magnitude, sf::Time& deltaTime) {
	sf::Vector2 position = this->getPosition();
	position.x += magnitude * mSpeed * deltaTime.asMilliseconds();
	position.x = std::clamp(position.x, 32.0f, 480.0f);
	this->setPosition(position);
}

float Bumper::GetFriction() { return mFriction; }