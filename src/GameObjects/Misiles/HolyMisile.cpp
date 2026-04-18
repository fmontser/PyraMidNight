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
		setOrigin(getGlobalBounds().getCenter()); //TODO check?
		setScale({1.5f,-1.5f});
	}

	void HolyMisile::Update(const sf::Time &deltaTime) {
		if (!mFlashEnabled)
			EnableFlashEffect();
		AnimateFrame(deltaTime);
		Misile::Update(deltaTime);
	}

	ICollidable::Info HolyMisile::OnCollision(ICollidable &collider) {
		if (collider.CollidableType == ICollidable::Type::POWER_UP) {
			auto& powerUp = static_cast<PowerUp&>(collider);
			auto cpos = powerUp.GetCollisionPoint(getGlobalBounds());

			if (cpos != std::nullopt && powerUp.PowerUpType == PowerUp::Type::GHOST) {
				//TODO impact sound effect
				auto sb = ResourceManager::GetAudio(PATH_AUD_COIN_IN);
				AudioManager::Play({sb, VOL_AUD_COIN_IN, PolySound::Type::SFX, false});
				mIsDestroyed = true;
				return { CollidableType, mIsDestroyed, 1.0f , cpos };
			}
		}
		return { CollidableType, mIsDestroyed, 0.0f , std::nullopt };
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