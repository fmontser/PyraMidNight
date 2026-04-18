#include <SFML/Graphics/Color.hpp>
#include "ResourceManager.hpp"
#include "RenderManager.hpp"
#include "AudioManager.hpp"
#include "MagicPuP.hpp"
#include "Bumper.hpp"
#include "Flash.hpp"

namespace pyramidnight {
	
	MagicPuP::MagicPuP(const sf::Texture &texture) : PowerUp(texture) {
		PowerUpType = PowerUp::Type::MAGIC;
		mSpeed *= ANI_MAGIC_V_SPEED_MOD;
		mFlashEnabled = false;
		mIsDestroyed = false;
		mAnimationDelta = 0.0f;
		mAnimationRect = {{0,0},{32,32}};
		setTextureRect(mAnimationRect);
		mSpriteRect = getTextureRect();
		mTextureSize = getTexture().getSize();
		setOrigin(getGlobalBounds().getCenter());
		setScale({1.5f,1.5f});
	}

	void MagicPuP::Update(const sf::Time &deltaTime) {
		if (!mFlashEnabled)
			EnableFlashEffect();
		AnimateFrame(deltaTime);
		PowerUp::Update(deltaTime);
	}

	ICollidable::Info MagicPuP::OnCollision(ICollidable &collider) {
		if (collider.CollidableType == ICollidable::Type::BUMPER) {
			auto& bumper = static_cast<Bumper&>(collider);
			auto cpos = GetCollisionPoint(bumper.getGlobalBounds());

			if (cpos != std::nullopt) {
				auto sb = ResourceManager::GetAudio(PATH_AUD_COIN_IN);
				AudioManager::Play({sb, VOL_AUD_COIN_IN, PolySound::Type::SFX, false});
				mIsDestroyed = true;
				return { CollidableType, mIsDestroyed, PWRUP_MAGIC_DURATION , cpos };
			}
		}
		return { CollidableType, mIsDestroyed, 0.0f , std::nullopt };
	}

	void MagicPuP::AnimateFrame(const sf::Time &deltaTime) {
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

	void MagicPuP::EnableFlashEffect() {
		mFlashEnabled = true;
		RenderManager::DisplayEffect(std::make_unique<Flash>(
			-1.0f, EFF_FLASH_SCOREPUP_LAPSE, EFF_FLASH_SCOREPUP_COLOR, getColor(), shared_from_this()));
	}
}