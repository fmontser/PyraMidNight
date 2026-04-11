#include <SFML/Graphics/Color.hpp>
#include "ResourceManager.hpp"
#include "RenderManager.hpp"
#include "AudioManager.hpp"
#include "ExtraCreditPuP.hpp"
#include "Bumper.hpp"
#include "Flash.hpp"

namespace pyramidnight {
	
	ExtraCreditPuP::ExtraCreditPuP(const sf::Texture &texture, uint32_t scoreMod) : PowerUp(texture) {
		PowerUpType = PowerUp::Type::SCORE;
		mScoreMod = scoreMod;
		mRotation = 0.0f;
		setOrigin(getGlobalBounds().getCenter());
	}

	ICollidable::Info ExtraCreditPuP::OnCollision(ICollidable &collider) {
		if (collider.CollidableType == ICollidable::Type::BUMPER) {
			auto& bumper = static_cast<Bumper&>(collider);
			auto cpos = bumper.GetCollisionPoint(getGlobalBounds());

			if (cpos != std::nullopt) {
				auto sb = ResourceManager::GetAudio(PATH_AUD_PWRUP_0);
				AudioManager::Play({sb, VOL_AUD_PWRUP_0, PolySound::Type::SFX, false});
				mIsDestroyed = true;
				return { CollidableType, mIsDestroyed, mScoreMod, cpos };
			}
		}
		return { CollidableType, mIsDestroyed, 0, std::nullopt };
	}

	void ExtraCreditPuP::EnableFlashEffect() {
		RenderManager::DisplayEffect(std::make_unique<Flash>(
			-1.0f, EFF_FLASH_SCOREPUP_LAPSE, EFF_FLASH_SCOREPUP_COLOR, getColor(), shared_from_this()));
	}
}