#include <algorithm>
#include <cmath>
#include "Ball.hpp"
#include "AudioManager.hpp"
#include "ResourceManager.hpp"


namespace pyramidnight {

	Ball::Ball(const sf::Texture& texture) : sf::Sprite(texture) {
		mSpeed = BALL_INIT_SPEED;
		mDirection = BALL_INIT_DIR;
		mRadius = texture.getSize().x / 2;
		mDistance = 1.0f;
		mState = State::DOCKED;
		setOrigin({mRadius,mRadius});
		ResetPos(BALL_INIT_POS);
	}

	void Ball::Launch() {
		if (mState == State::DOCKED) {
			mState = State::PLAYING;
			auto sb = ResourceManager::GetAudio(PATH_AUD_BALL_LAUNCH);
			AudioManager::Play({sb, VOL_AUD_BALL_LAUNCH, PolySound::Type::SFX, false});
		}
	}

	void Ball::ResetPos(const sf::Vector2f &bumperPos) {
		auto newPos = bumperPos + BALL_DOCKED_OFFSET;
		setPosition(newPos);
		mDirection = BALL_INIT_DIR;
		mState = State::DOCKED;
	}

	void Ball::Update(const sf::Vector2f &bumperPos, const sf::Time& deltaTime) {
		switch (mState) {
			case State::PLAYING: Move(deltaTime); break;
			case State::DOCKED: ResetPos(bumperPos); break;
			default: break;
		}
	}

	void Ball::Bounce(const sf::Sprite& obj) {
		auto rPos = obj.getPosition();
		auto rSize = obj.getGlobalBounds().size;
		auto bPos = getPosition();
		
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

	const Ball::State &Ball::GetState() const { return mState; }

	float Ball::GetRadius() const { return mRadius; }

	void Ball::Move(const sf::Time& deltaTime) {
		sf::Vector2f position = getPosition();
		auto deltaTimeMs = deltaTime.asMilliseconds();

		position.x += mDirection.x * mSpeed * deltaTimeMs;
		position.y += mDirection.y * mSpeed * deltaTimeMs;
		setPosition(position);
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


