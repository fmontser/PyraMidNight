#include "ExtraScore.hpp"
#include "Bumper.hpp"

namespace pyramidnight {
	
	ExtraScore::ExtraScore(const sf::Texture &texture, uint32_t scoreMod) : PowerUp(texture) {
		mScoreMod = scoreMod;
	}

	ICollidable::Info ExtraScore::OnCollision(ICollidable &collider) {
		if (collider.CollidableType == ICollidable::CollidableType::BUMPER) {
			auto& bumper = static_cast<Bumper&>(collider);
			auto cpos = bumper.GetCollisionPoint(getGlobalBounds());
			if (cpos != std::nullopt) {
				return {CollidableType, true, mScoreMod, cpos };
			}
		}
		return {CollidableType, false, 0, std::nullopt };
	}
}