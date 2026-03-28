#include <algorithm>
#include <cmath>
#include "Ball.hpp"

Ball::Ball(const sf::Texture& texture) : sf::Sprite(texture) {
	mSpeed = 0.6;
	mDirection = {-1, -1};
	mRadius = 16;
	setOrigin({16,16});
	ResetPos({256, 832});
}

void Ball::Launch() {
	mState = State::PLAYING;
}

void Ball::ResetPos(const sf::Vector2f &bumperPos) {
	sf::Vector2f bumperOffset({64,-18});
	auto newPos = bumperPos + bumperOffset;
	setPosition(newPos);
	mDirection = {-1,-1};
	mState = State::DOCKED;
}

void Ball::Update(const sf::Vector2f &bumperPos, const sf::Time& deltaTime) {
	switch (mState)	{
		case State::PLAYING: Move(deltaTime); break;
		case State::DOCKED: ResetPos(bumperPos); break;
		default: break;
	}
}

void Ball::Bounce(const sf::Sprite& obj, float distance) {
	auto rPos = obj.getPosition();
	auto rSize = obj.getGlobalBounds().size;
	auto bPos = getPosition();
	
	ResolveOverlap(distance);
	auto isBounceHorizontal = (bPos.x < rPos.x || bPos.x > (rPos.x + rSize.x));
	auto isBounceVertical = (bPos.y < rPos.y || bPos.y > (rPos.y + rSize.y));

	if (isBounceHorizontal && isBounceVertical)
		mDirection = -mDirection;
	else if (isBounceHorizontal)
		mDirection.x = -mDirection.x;
	else if (isBounceVertical)
		mDirection.y = -mDirection.y;
}

void Ball::ApplyBumperMod(const sf::Sprite& bumper) {
	
	float bumperWidth = bumper.getGlobalBounds().size.x;
	float bumperX = bumper.getPosition().x + bumperWidth / 2.0f;
	float modFactor = (getPosition().x - bumperX) / (bumperWidth / 2.0f);
	float speed = std::sqrt(std::powf(mDirection.x, 2) + std::powf(mDirection.y, 2));
	
	// Apply control modification
	mDirection.x = modFactor;
	//Keep vector speed and upwards direction
	mDirection.y = -std::sqrt(std::max(0.0f, std::powf(speed, 2) - std::powf(mDirection.x, 2))); 
}

const Ball::State &Ball::GetState() const { return mState; }
const float Ball::GetRadius() const { return mRadius; }

//TODO hardcoded values...get playarea rect
void Ball::Move(const sf::Time& deltaTime) {
	sf::Vector2f position = getPosition();
	auto deltaTimeMs = deltaTime.asMilliseconds();

	position.x += mDirection.x * mSpeed * deltaTimeMs;
	position.y += mDirection.y * mSpeed * deltaTimeMs;
	setPosition(position);
}

void Ball::ResolveOverlap(float distance) {
	float overlap = std::abs(distance - mRadius);
	auto invertedDirection = -mDirection;
	auto pos = this->getPosition();

	pos += (invertedDirection.normalized() * overlap);
	this->setPosition(pos);
}
