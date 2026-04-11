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
		mAnimationRect = {{0,0},{32,32}};
		setTextureRect(mAnimationRect);
		mSpriteRect = getTextureRect();
		mTextureSize = getTexture().getSize();
		setOrigin(getGlobalBounds().getCenter());
		GenerateDirection();
	}

	void ExtraCreditPuP::Update(const sf::Time &deltaTime)	{
		AnimateFrame(deltaTime);
		ApplyCurvedMovement(deltaTime);
		PowerUp::Update(deltaTime);
	}

	ICollidable::Info ExtraCreditPuP::OnCollision(ICollidable &collider) {
		if (collider.CollidableType == ICollidable::Type::BUMPER) {
			auto& bumper = static_cast<Bumper&>(collider);
			auto cpos = bumper.GetCollisionPoint(getGlobalBounds());

			if (cpos != std::nullopt) {
				auto sb = ResourceManager::GetAudio(PATH_AUD_COIN_IN);
				AudioManager::Play({sb, VOL_AUD_COIN_IN, PolySound::Type::SFX, false});
				mIsDestroyed = true;
				return { CollidableType, mIsDestroyed, 1.0f , cpos };
			}
		}
		return { CollidableType, mIsDestroyed, 0.0f, std::nullopt };
	}

	//TODO hardcorded values
	void ExtraCreditPuP::ApplyCurvedMovement(const sf::Time &deltaTime) {
		mDeltaX += mDirection.x * 8.0f * deltaTime.asSeconds();
		mDeltaY += 10.0f * deltaTime.asSeconds();
		move({mDeltaX, mDeltaY});
		sf::Vector2f position(getPosition());
		position.x = std::clamp(position.x, 54.0f, 592.0f);
		setPosition(position);
	}

	// TODO remove hardcoded
	void ExtraCreditPuP::EnableFlashEffect() {
		RenderManager::DisplayEffect(std::make_unique<Flash>(
			-1.0f, 0.042f, sf::Color::Red, getColor(), shared_from_this()));
	}

	void ExtraCreditPuP::GenerateDirection() { 
		static std::random_device rd; 
		static std::mt19937 gen(rd()); 
		std::uniform_int_distribution<int> x(-1, 0);
		
		// zero is right direction
		mDirection.x = x(gen) == 0 ? 1 : -1;
	}

	//TODO remove hardcoded values
	void ExtraCreditPuP::AnimateFrame(const sf::Time &deltaTime) {

		mAnimationDelta += deltaTime.asSeconds();
		if (mAnimationDelta >= 0.1f) {
			size_t newFrameX = mAnimationRect.position.x + mSpriteRect.size.x;
			
			if (newFrameX > mTextureSize.x)
				newFrameX = 0;
			mAnimationRect.position.x = newFrameX;
			setTextureRect(mAnimationRect);
			mAnimationDelta = 0;
		}
	}
}