#include <SFML/Graphics/Color.hpp>
#include <random>
#include <algorithm>
#include "ResourceManager.hpp"
#include "RenderManager.hpp"
#include "AudioManager.hpp"
#include "GhostPuP.hpp"
#include "Bumper.hpp"
#include "Flash.hpp"

namespace pyramidnight {
	
	GhostPuP::GhostPuP(const sf::Texture &texture) : PowerUp(texture) {
		PowerUpType = PowerUp::Type::GHOST;
		mBumperSpeedPenalty = 1.0f;
		mSpeed = PWRUP_GHOST_SPEED;
		mDeltaX = 0.0f;
		mDeltaY = 0.0f;
		mDiveTimer = 0.0f;
		mDiveLimit = GenerateHoverTime();
		mFlashEnabled = false;
		mAttackTimer = 0.0f;
		mAttackLimit = PWRUP_GHOST_PENALTY_TIME;
		mIsAttacking = false;

		mAnimationDelta = 0.0f;
		mTextureSize = getTexture().getSize();
		mAnimationRect = {{0,0},{64,64}};
		setTextureRect(mAnimationRect);
		mSpriteRect = getTextureRect();
		setOrigin(getGlobalBounds().getCenter());
		setColor(PWRUP_GHOST_COLOR);
		mDirection.x = GenerateDirection();
		auto sb = ResourceManager::GetAudio(PATH_AUD_GHOST_SPAWN);
		AudioManager::Play({sb, VOL_AUD_GHOST_SPAWN, PolySound::Type::SFX, false});
	}

	void GhostPuP::Update(const sf::Time &deltaTime) {
 		if (!mFlashEnabled)
			EnableFlashEffect();
		AnimateFrame(deltaTime);
		ApplyGhostlyMovement(deltaTime);
		UpdateAttack(deltaTime);
		MirrorSprite();
		PowerUp::Update(deltaTime);
	}

	ICollidable::Info GhostPuP::OnCollision(ICollidable &collider) {
		if (collider.CollidableType == ICollidable::Type::BUMPER) {
			auto& bumper = static_cast<Bumper&>(collider);
			auto cpos = bumper.GetCollisionPoint(getGlobalBounds());

			if (cpos != std::nullopt && !mIsAttacking && !mIsDestroyed) {
				auto sb = ResourceManager::GetAudio(PATH_AUD_GHOST_ATTACK);
				AudioManager::Play({sb, VOL_AUD_GHOST_ATTACK, PolySound::Type::SFX, false});
				mIsAttacking = true;
				EnableAttackFlashEffect();
				return { CollidableType, mIsDestroyed, mBumperSpeedPenalty , cpos };
			}
			// stick to bumper while attacking
			if (cpos != std::nullopt && !mIsDestroyed)
				setPosition(*cpos);
		}
		return { CollidableType, mIsDestroyed, mBumperSpeedPenalty, std::nullopt };
	}

	void GhostPuP::ApplyGhostlyMovement(const sf::Time &deltaTime) {
		if (mIsAttacking)
			return;
		auto deltaTimeSec = deltaTime.asSeconds();
		mDeltaX += mDirection.x * ANI_GHOST_H_SPEED_MOD * deltaTimeSec;
		mDeltaY += mDirection.y * ANI_GHOST_V_SPEED_MOD * deltaTimeSec;

		if (mDeltaX < -ANI_GHOST_SWING_RANGE || mDeltaX > ANI_GHOST_SWING_RANGE)
			mDirection.x *= -1;
		if (mDiveTimer < mDiveLimit) {
			mDiveTimer += deltaTimeSec;
			mDirection.y *= -1 ;
		}

		move({mDeltaX, mDeltaY});
		sf::Vector2f position(getPosition());
		setPosition(position);
	}

	void GhostPuP::UpdateAttack(const sf::Time &deltaTime) {
		if (mIsAttacking) {
			mAttackTimer += deltaTime.asSeconds();
			mBumperSpeedPenalty = PWRUP_GHOST_PENALTY_MOD;
			//setColor(PWRUP_GHOST_ATTACK_COLOR);
		}
		if (mIsAttacking && (mAttackTimer >= mAttackLimit)) {
			mBumperSpeedPenalty = 1.0f;
			mIsAttacking = false;
			mIsDestroyed = true;
			//setColor(PWRUP_GHOST_COLOR);
		}
	}

	void GhostPuP::EnableFlashEffect() {
		mFlashEnabled = true;
		RenderManager::DisplayEffect(std::make_unique<Flash>(
			-1.0f, EFF_FLASH_GHOST_LAPSE, EFF_FLASH_GHOST_COLOR, getColor(), shared_from_this()));
	}

	void GhostPuP::EnableAttackFlashEffect() {
		RenderManager::DisplayEffect(std::make_unique<Flash>(
			PWRUP_GHOST_PENALTY_TIME, EFF_FLASH_GHOST_LAPSE, EFF_FLASH_GHOST_ATTACK_COLOR, getColor(), shared_from_this()));
	}

	int GhostPuP::GenerateDirection() { 
		static std::random_device rd; 
		static std::mt19937 gen(rd()); 
		std::uniform_int_distribution<int> x(-1, 0);
		
		// zero is right direction
		return x(gen) == 0 ? 1 : -1;
	}

	float GhostPuP::GenerateHoverTime() { 
		static std::random_device rd; 
		static std::mt19937 gen(rd()); 
		std::uniform_real_distribution<float>
			t(PWRUP_GHOST_HOVER_TIME_MIN, PWRUP_GHOST_HOVER_TIME_MAX);
		return t(gen);
	}

	void GhostPuP::AnimateFrame(const sf::Time &deltaTime) {
		mAnimationDelta += deltaTime.asSeconds();
		if (mAnimationDelta >= ANI_GHOST_FRAMERATE) {
			size_t newFrameX = mAnimationRect.position.x + mSpriteRect.size.x;
			
			if (newFrameX >= mTextureSize.x)
				newFrameX = 0;
			mAnimationRect.position.x = newFrameX;
			setTextureRect(mAnimationRect);
			mAnimationDelta = 0;
		}
	}
	
	void GhostPuP::MirrorSprite() {
		sf::Vector2f mirror(getScale());
		mirror.x = mDirection.x;
		setScale(mirror);
	}
}