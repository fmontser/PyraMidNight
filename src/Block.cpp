#include "Block.hpp"

Block::Block(const sf::Texture& texture, int8_t hitPoints) : sf::Sprite(texture) {
	this->hitPoints = hitPoints;
}

bool Block::Damage() {
	hitPoints--;
	if (hitPoints == 0)
		return true;
	return false;
}
