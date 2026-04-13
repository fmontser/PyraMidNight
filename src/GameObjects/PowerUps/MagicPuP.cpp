#include <SFML/Graphics/Color.hpp>
#include "ResourceManager.hpp"
#include "RenderManager.hpp"
#include "AudioManager.hpp"
#include "MagicPuP.hpp"
#include "Flash.hpp"

namespace pyramidnight {
	
	MagicPuP::MagicPuP(const sf::Texture &texture) : PowerUp(texture) {
		PowerUpType = PowerUp::Type::MAGIC;
		mFlashEnabled = false;
		mIsDestroyed = false;
		setOrigin(getGlobalBounds().getCenter());
	}

	void MagicPuP::Update(const sf::Time &deltaTime) {
		if (!mFlashEnabled)
			EnableFlashEffect();
		PowerUp::Update(deltaTime);
	}

	//TODO hardcoded damage
	ICollidable::Info MagicPuP::OnCollision(ICollidable &collider) {
		if (collider.CollidableType == ICollidable::Type::POWER_UP) {
			auto& powerUp = static_cast<PowerUp&>(collider);
 			auto cpos = powerUp.GetCollisionPoint(getGlobalBounds());

			if (cpos != std::nullopt && powerUp.PowerUpType == PowerUp::Type::GHOST) {
				auto sb = ResourceManager::GetAudio(PATH_AUD_PWRUP_0);
				AudioManager::Play({sb, VOL_AUD_PWRUP_0, PolySound::Type::SFX, false});
				mIsDestroyed = true;
				return { CollidableType, mIsDestroyed, 1.0f, cpos };
			}
		}
		return { CollidableType, mIsDestroyed, 0.0f, std::nullopt };
	}

	void MagicPuP::EnableFlashEffect() {
		mFlashEnabled = true;
		RenderManager::DisplayEffect(std::make_unique<Flash>(
			-1.0f, EFF_FLASH_SCOREPUP_LAPSE, EFF_FLASH_SCOREPUP_COLOR, getColor(), shared_from_this()));
	}
}