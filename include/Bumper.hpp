#pragma once
#include <SFML/Graphics.hpp>

class Bumper : public sf::Sprite {
	public:
		Bumper(const sf::Texture& texture);

		void Move(int8_t magnitude, sf::Time& deltaTime);

	private:
		float mSpeed;
};