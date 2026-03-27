#pragma once
#include <SFML/Graphics.hpp>

class Block : public sf::Sprite {
	public:
		Block(const sf::Texture& texture, int8_t hitPoints = 1);

		bool Damage();
	private:
		int8_t hitPoints;
};