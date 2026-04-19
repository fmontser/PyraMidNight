#include <SFML/Graphics/Color.hpp>
#include "ResourceManager.hpp"
#include "RenderManager.hpp"
#include "AudioManager.hpp"
#include "HolyMisile.hpp"
#include "Bumper.hpp"
#include "PowerUp.hpp"
#include "Flash.hpp"

namespace pyramidnight {
	
	HolyMisile::HolyMisile(const sf::Texture &texture) : Misile(texture) {
		MisileType = Misile::Type::HOLY_MISILE;
		mSpeed *= ANI_HOLYMISILE_V_SPEED_MOD;
		mFlashEnabled = false;
		mIsDestroyed = false;
		mAnimationDelta = 0.0f;
		mAnimationRect = {{0,0},{32,32}};
		setTextureRect(mAnimationRect);
		mSpriteRect = getTextureRect();
		mTextureSize = getTexture().getSize();
		setOrigin(getGlobalBounds().getCenter());
		setScale({1.5f,-1.5f});
	}

	void HolyMisile::Update(const sf::Time &deltaTime) {
		if (!mFlashEnabled)
			EnableFlashEffect();
		AnimateFrame(deltaTime);
		Misile::Update(deltaTime);
	}

	ICollidable::Info HolyMisile::OnCollision(ICollidable &collider) {
		switch (collider.CollidableType) {
			case ICollidable::Type::POWER_UP: return OnPowerUpCollision(collider);
			default: break;
		}
		return { CollidableType, false, 0, std::nullopt };
	}

	ICollidable::Info HolyMisile::OnPowerUpCollision(ICollidable &collider) {
		auto& pup = static_cast<PowerUp&>(collider);
		auto cpos = GetCollisionPoint(pup.getGlobalBounds());
		if (cpos != std::nullopt) {
			switch(pup.PowerUpType) {
				case PowerUp::Type::GHOST: {return OnGhostCollision(cpos); break;}
				default: break;
			}
			return { CollidableType, false, 0, cpos };
		}
		return { CollidableType, false, 0, std::nullopt };
	}

	ICollidable::Info HolyMisile::OnGhostCollision(std::optional<sf::Vector2f>& cpos) {
		//TODO impact sound effect
		auto sb = ResourceManager::GetAudio(PATH_AUD_COIN_IN);
		AudioManager::Play({sb, VOL_AUD_COIN_IN, PolySound::Type::SFX, false});
		mIsDestroyed = true;
		return { CollidableType, mIsDestroyed, 1.0f , cpos };
	}

	void HolyMisile::AnimateFrame(const sf::Time &deltaTime) {
		mAnimationDelta += deltaTime.asSeconds();
		if (mAnimationDelta >= ANI_MAGIC_FRAMERATE) {
			size_t newFrameX = mAnimationRect.position.x + mSpriteRect.size.x;
			
			if (newFrameX >= mTextureSize.x)
				newFrameX = 0;
			mAnimationRect.position.x = newFrameX;
			setTextureRect(mAnimationRect);
			mAnimationDelta = 0;
		}
	}

	void HolyMisile::EnableFlashEffect() {
		mFlashEnabled = true;
		RenderManager::DisplayEffect(std::make_unique<Flash>(
			-1.0f, EFF_FLASH_SCOREPUP_LAPSE, EFF_FLASH_SCOREPUP_COLOR, getColor(), shared_from_this()));
	}
}