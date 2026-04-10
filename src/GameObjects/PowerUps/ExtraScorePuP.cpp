#include "ExtraScorePuP.hpp"
#include "Bumper.hpp"

namespace pyramidnight {
	
	ExtraScorePuP::ExtraScorePuP(const sf::Texture &texture, uint32_t scoreMod) : PowerUp(texture) {
		mScoreMod = scoreMod;
		PowerUpType = PowerUp::Type::SCORE;
	}

	ICollidable::Info ExtraScorePuP::OnCollision(ICollidable &collider) {
		if (collider.CollidableType == ICollidable::Type::BUMPER) {
			auto& bumper = static_cast<Bumper&>(collider);
			auto cpos = bumper.GetCollisionPoint(getGlobalBounds());
			if (cpos != std::nullopt) {
				return { CollidableType, true, mScoreMod, cpos };
			}
		}
		return { CollidableType, false, 0, std::nullopt };
	}
}