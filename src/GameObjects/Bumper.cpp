#include <algorithm>
#include "Bumper.hpp"

namespace pyramidnight {
	
	Bumper::Bumper(const sf::Texture& texture) : sf::Sprite(texture) {
		mSpeed = BMPR_INIT_SPEED;
	}
	
	void Bumper::Move(int8_t magnitude, sf::Time& deltaTime, bool fine, bool coarse) {
		sf::Vector2 position = this->getPosition();
		if (fine && !coarse)
			mSpeed *= BMPR_FINE_SPEED_MOD;
		else if (!fine && coarse)
			mSpeed *= BMPR_COARSE_SPEED_MOD;

		position.x += magnitude * mSpeed * deltaTime.asMilliseconds();
		position.x = std::clamp(position.x, BMPR_MV_LIMIT_L, BMPR_MV_LIMIT_R);
		this->setPosition(position);
		mSpeed = BMPR_INIT_SPEED;
	}

}