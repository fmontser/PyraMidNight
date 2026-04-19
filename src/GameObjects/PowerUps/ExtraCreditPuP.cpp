#include <SFML/Graphics/Color.hpp>
#include <random>
#include <algorithm>
#include "ResourceManager.hpp"
#include "RenderManager.hpp"
#include "AudioManager.hpp"
#include "ExtraCreditPuP.hpp"
#include "Bumper.hpp"
#include "Flash.hpp"

namespace pyramidnight {
	
	ExtraCreditPuP::ExtraCreditPuP(const sf::Texture &texture) : PowerUp(texture) {
		PowerUpType = PowerUp::Type::CREDIT;
		mDeltaX = 0.0f;
		mDeltaY = 0.0f;
		mFlashEnabled = false;
		mAnimationDelta = 0.0f;
		mAnimationRect = {{0,0},{32,32}};
		setTextureRect(mAnimationRect);
		mSpriteRect = getTextureRect();
		mTextureSize = getTexture().getSize();
		setOrigin(getGlobalBounds().getCenter());
		GenerateDirection();
	}

	void ExtraCreditPuP::Update(const sf::Time &deltaTime) {
		if (!mFlashEnabled)
			EnableFlashEffect();
		AnimateFrame(deltaTime);
		ApplyCurvedMovement(deltaTime);
		PowerUp::Update(deltaTime);
	}

	ICollidable::Info ExtraCreditPuP::OnCollision(ICollidable &collider) {
		if (collider.CollidableType == ICollidable::Type::BUMPER) {
			auto& bumper = static_cast<Bumper&>(collider);
			auto cpos = GetCollisionPoint(bumper.getGlobalBounds());

			if (cpos != std::nullopt) {
				auto sb = ResourceManager::GetAudio(PATH_AUD_COIN_IN);
				AudioManager::Play({sb, VOL_AUD_COIN_IN, PolySound::Type::SFX, false});
				mIsDestroyed = true;
				return { CollidableType, mIsDestroyed, 1.0f , cpos };
			}
		}
		return { CollidableType, mIsDestroyed, 0.0f, std::nullopt };
	}

	void ExtraCreditPuP::ApplyCurvedMovement(const sf::Time &deltaTime) {
		mDeltaX += mDirection.x * ANI_COIN_H_SPEED_MOD * deltaTime.asSeconds();
		mDeltaY += ANI_COIN_V_SPEED_MOD * deltaTime.asSeconds();
		move({mDeltaX, mDeltaY});
		sf::Vector2f position(getPosition());
		position.x = std::clamp(position.x, 54.0f, 592.0f);
		setPosition(position);
	}

	void ExtraCreditPuP::EnableFlashEffect() {
		mFlashEnabled = true;
		RenderManager::DisplayEffect(std::make_unique<Flash>(
			-1.0f, EFF_FLASH_CREDITUP_LAPSE, EFF_FLASH_CREDITUP_COLOR, getColor(), shared_from_this()));
	}

	void ExtraCreditPuP::GenerateDirection() { 
		static std::random_device rd; 
		static std::mt19937 gen(rd()); 
		std::uniform_int_distribution<int> x(-1, 0);
		
		// zero is right direction
		mDirection.x = x(gen) == 0 ? 1 : -1;
	}

	void ExtraCreditPuP::AnimateFrame(const sf::Time &deltaTime) {
		mAnimationDelta += deltaTime.asSeconds();
		if (mAnimationDelta >= ANI_COIN_FRAMERATE) {
			size_t newFrameX = mAnimationRect.position.x + mSpriteRect.size.x;
			
			if (newFrameX >= mTextureSize.x)
				newFrameX = 0;
			mAnimationRect.position.x = newFrameX;
			setTextureRect(mAnimationRect);
			mAnimationDelta = 0;
		}
	}
}