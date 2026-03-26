#pragma once
#include <SFML/Graphics.hpp>

class Ball : public sf::Sprite {
	public:
		Ball(const sf::Texture& texture);

		void Move(int32_t magnitude, sf::Time& deltaTime);


	private:
		float mSpeed;
};