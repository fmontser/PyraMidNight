#include <algorithm>
#include "Bumper.hpp"
#include"Common.hpp"

Bumper::Bumper(const sf::Texture& texture) : sf::Sprite(texture) {
	mSpeed = fkd::BMPR_INIT_SPEED;
}

void Bumper::Move(int8_t magnitude, sf::Time& deltaTime) {
	sf::Vector2 position = this->getPosition();
	position.x += magnitude * mSpeed * deltaTime.asMilliseconds();
	position.x = std::clamp(position.x, fkd::BMPR_MV_LIMIT_L, fkd::BMPR_MV_LIMIT_R);
	this->setPosition(position);
}