#include <algorithm>
#include "Bumper.hpp"

namespace fknd {
	
	Bumper::Bumper(const sf::Texture& texture) : sf::Sprite(texture) {
		mSpeed = BMPR_INIT_SPEED;
	}
	
	void Bumper::Move(int8_t magnitude, sf::Time& deltaTime) {
		sf::Vector2 position = this->getPosition();
		position.x += magnitude * mSpeed * deltaTime.asMilliseconds();
		position.x = std::clamp(position.x, BMPR_MV_LIMIT_L, BMPR_MV_LIMIT_R);
		this->setPosition(position);
	}

}