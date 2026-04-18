#include <SFML/Graphics/Color.hpp>
#include "ResourceManager.hpp"
#include "RenderManager.hpp"
#include "AudioManager.hpp"
#include "ExtraScorePuP.hpp"
#include "Bumper.hpp"
#include "Flash.hpp"

namespace pyramidnight {
	
	ExtraScorePuP::ExtraScorePuP(const sf::Texture &texture, uint32_t scoreMod) : PowerUp(texture) {
		PowerUpType = PowerUp::Type::SCORE;
		mScoreMod = scoreMod;
		mFlashEnabled = false;
		mRotation = 0.0f;
		setOrigin(getGlobalBounds().getCenter());
	}

	void ExtraScorePuP::Update(const sf::Time &deltaTime) {
		if (!mFlashEnabled)
			EnableFlashEffect();
		PowerUp::Update(deltaTime);
	}

	//TODO move rotation to RenderEffect
	ICollidable::Info ExtraScorePuP::OnCollision(ICollidable &collider) {
		if (collider.CollidableType == ICollidable::Type::BUMPER) {
			auto& bumper = static_cast<Bumper&>(collider);
			auto cpos = GetCollisionPoint(bumper.getGlobalBounds());
			mRotation += 5.0f;
			setRotation(sf::degrees(mRotation));
			if (cpos != std::nullopt) {
				auto sb = ResourceManager::GetAudio(PATH_AUD_PWRUP_0);
				AudioManager::Play({sb, VOL_AUD_PWRUP_0, PolySound::Type::SFX, false});
				mIsDestroyed = true;
				return { CollidableType, mIsDestroyed, static_cast<float>(mScoreMod), cpos };
			}
		}
		return { CollidableType, mIsDestroyed, 0.0f, std::nullopt };
	}

	void ExtraScorePuP::EnableFlashEffect() {
		mFlashEnabled = true;
		RenderManager::DisplayEffect(std::make_unique<Flash>(
			-1.0f, EFF_FLASH_SCOREPUP_LAPSE, EFF_FLASH_SCOREPUP_COLOR, getColor(), shared_from_this()));
	}
}