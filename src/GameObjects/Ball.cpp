#include <algorithm>
#include <cmath>
#include "Ball.hpp"
#include "AudioManager.hpp"
#include "ResourceManager.hpp"
#include "Obstacle.hpp"
#include "Bumper.hpp"
#include "Block.hpp"

namespace pyramidnight {

	Ball::Ball(const sf::Texture& texture) : sf::Sprite(texture) {
		CollidableType = ICollidable::Type::BALL;
		IsDynamic = true;
		mSpeed = BALL_INIT_SPEED;
		mDirection = BALL_INIT_DIR;
		mRadius = texture.getSize().x / 2;
		mDistance = 1.0f;
		mState = State::DOCKED;
		setOrigin({mRadius,mRadius});
		Dock(BALL_INIT_POS);
	}

	Ball::State Ball::Update(UpdateBall update) {
		switch (mState) {
			case State::PLAYING: Move(update.deltaTime); CheckDeath(update.deathArea); break;
			case State::DOCKED: Dock(update.bumperPos); Launch(update.action); break;
			case State::DEAD: break;
			default: break;
		}
		return mState;
	}

	ICollidable::Info Ball::OnCollision(ICollidable &collider) {
		switch (collider.CollidableType) {
			case ICollidable::Type::BLOCK: return OnBlockCollision(collider);
			case ICollidable::Type::OBSTACLE: return OnObstacleCollision(collider);
			case ICollidable::Type::BUMPER: return OnBumperCollision(collider);
			default: break;
		}
		return { CollidableType, false, 0, std::nullopt };
	}

	void Ball::Move(const sf::Time& deltaTime) {
		sf::Vector2f position = getPosition();
		auto deltaTimeMs = deltaTime.asMilliseconds();

		position.x += mDirection.x * mSpeed * deltaTimeMs;
		position.y += mDirection.y * mSpeed * deltaTimeMs;
		setPosition(position);
	}

	void Ball::CheckDeath(const sf::RectangleShape& deathArea) {
		if (deathArea.getGlobalBounds().contains(getPosition()))
			mState = State::DEAD;
	}

	void Ball::Launch(bool action) {
		if (mState == State::DOCKED && action) {
			mState = State::PLAYING;
			auto sb = ResourceManager::GetAudio(PATH_AUD_BALL_LAUNCH);
			AudioManager::Play({sb, VOL_AUD_BALL_LAUNCH, PolySound::Type::SFX, false});
		}
	}

	void Ball::Dock(const sf::Vector2f &bumperPos) {
		auto newPos = bumperPos + BALL_DOCKED_OFFSET;
		setPosition(newPos);
		mDirection = BALL_INIT_DIR;
		mState = State::DOCKED;
	}

	void Ball::Bounce(const sf::Sprite& obj) {
		auto rPos = obj.getPosition();
		auto rSize = obj.getGlobalBounds().size;
		auto bPos = getPosition();
		
		//TODO fix overlap function
		ResolveOverlap();
		auto isBounceHorizontal = (bPos.x < rPos.x || bPos.x > (rPos.x + rSize.x));
		auto isBounceVertical = (bPos.y < rPos.y || bPos.y > (rPos.y + rSize.y));

		if (isBounceHorizontal && isBounceVertical)
			mDirection = -mDirection;
		else if (isBounceHorizontal)
			mDirection.x = -mDirection.x;
		else if (isBounceVertical)
			mDirection.y = -mDirection.y;
		auto sb = ResourceManager::GetAudio(PATH_AUD_BALL_BOUNCE);
		AudioManager::Play({sb, VOL_AUD_BALL_BOUNCE, PolySound::Type::SFX, false});
	}

	void Ball::ApplyBumperMod(const sf::Sprite& bumper) {

		// new ball direction depending on impact position
		float bumperWidth = bumper.getGlobalBounds().size.x;
		float bumperX = bumper.getPosition().x + bumperWidth / 2.0f;
		float modFactor = (getPosition().x - bumperX) / (bumperWidth / 2.0f);
		float normSpeed = std::sqrt(std::powf(mDirection.x, 2) + std::powf(mDirection.y, 2));

		if (std::abs(modFactor) < BMPR_ATK_DEADZONE)
			modFactor = (modFactor < 0) ? -BMPR_ATK_DEADZONE : BMPR_ATK_DEADZONE;
		mDirection.x = modFactor * BMPR_ATK_PWR;

		// keep upwards
		mDirection.y = -std::sqrt(std::max(0.0f, std::powf(normSpeed, 2) - std::powf(mDirection.x, 2)));
		auto sb = ResourceManager::GetAudio(PATH_AUD_BUMPER_BOUNCE);
		AudioManager::Play({sb, VOL_AUD_BUMPER_BOUNCE, PolySound::Type::SFX, false});
	}

	ICollidable::Info Ball::OnBlockCollision(ICollidable &collider) {
		auto& block = static_cast<Block&>(collider);
		auto cpos = GetCollisionPoint(block.getGlobalBounds());
		if (cpos != std::nullopt)
			Bounce(block);
		return { CollidableType, false, 0, cpos };
	}

	ICollidable::Info Ball::OnObstacleCollision(ICollidable &collider) {
		auto& obstacle = static_cast<Obstacle&>(collider);
		auto cpos = GetCollisionPoint(obstacle.getGlobalBounds());
		if (cpos != std::nullopt)
			Bounce(obstacle);
		return { CollidableType, false, 0, cpos };
	}

	ICollidable::Info Ball::OnBumperCollision(ICollidable &collider) {
		auto& bumper = static_cast<Bumper&>(collider);
		auto cpos = GetCollisionPoint(bumper.getGlobalBounds());
		if (cpos != std::nullopt) {
			Bounce(bumper);
			ApplyBumperMod(bumper);
		}
		return { CollidableType, false, 0, cpos };
	}

	std::optional<sf::Vector2f> Ball::GetCollisionPoint(const sf::FloatRect &rect) {
		sf::Vector2f closest {};
		auto bPos = getPosition();
		closest.x = std::clamp(bPos.x, rect.position.x, rect.position.x + rect.size.x);
		closest.y = std::clamp(bPos.y, rect.position.y, rect.position.y + rect.size.y);
		float distX = bPos.x - closest.x;
		float distY = bPos.y - closest.y;
		mDistance = std::sqrtf((distX * distX) + (distY * distY));

		if (mDistance <= mRadius)
			return closest; 
		return std::nullopt;
	}

	void Ball::ResolveOverlap() {
		// bounce back from clipping
		float overlap = std::abs(mDistance - mRadius);
		auto invertedDirection = -mDirection;
		auto pos = this->getPosition();

		pos += (invertedDirection.normalized() * overlap);
		this->setPosition(pos);
	}

}


