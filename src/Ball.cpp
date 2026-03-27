#include "Ball.hpp"
#include <algorithm>
#include <cmath>

Ball::Ball(const sf::Texture& texture) : sf::Sprite(texture) {
	mSpeed = 0.25;
	mDirection = {-1, -1};
	mRadius = getLocalBounds().size.x / 2;
	setOrigin({getLocalBounds().size.x / 2, getLocalBounds().size.y / 2});
	ResetPos({256, 832});
}

void Ball::Launch() {
	mState = State::PLAYING;
}

void Ball::ResetPos(const sf::Vector2f &bumperPos) {
	sf::Vector2f bumperOffset({64,-16});
	auto newPos = bumperPos + bumperOffset;
	setPosition(newPos);
	mState = State::DOCKED;
}

void Ball::Update(const sf::Vector2f &bumperPos, sf::Time& deltaTime) {
	switch (mState)	{
		case State::PLAYING: Move(deltaTime); break;
		case State::DOCKED: ResetPos(bumperPos); break;
		default: break;
	}
}

void Ball::Bounce(sf::Rect<float> rect, float distance) {
	auto rPos = rect.position;
	auto rSize = rect.size;
	auto bPos = getPosition();
	auto bRadius = mRadius;
	
	ResolveOverlap(distance);
	auto isBounceHorizontal = (bRadius < rPos.x || bRadius > (rPos.x + rSize.x));
	auto isBounceVertical = (bRadius < rPos.y || bRadius > (rPos.y + rSize.y));

	if (isBounceHorizontal && isBounceVertical)
		mDirection = -mDirection;
	else if (isBounceHorizontal)
		mDirection.x = -mDirection.x;
	else if (isBounceVertical)
		mDirection.y = -mDirection.y;
}

const Ball::State &Ball::GetState() const { return mState; }
const float Ball::GetRadius() const { return mRadius; }

//TODO hardcoded values...get playarea rect
void Ball::Move(sf::Time& deltaTime) {
	sf::Vector2f position = getPosition();
	auto deltaTimeMs = deltaTime.asMilliseconds();

	position.x += mDirection.x * mSpeed * deltaTimeMs;
	position.y += mDirection.y * mSpeed * deltaTimeMs;
	//TODO remove clamp on bounce() ready
	position.x = std::clamp(position.x, 48.0f, 560.0f);
	position.y = std::clamp(position.y, 48.0f, 880.0f);
	setPosition(position);
}

void Ball::ResolveOverlap(float distance) {
	float snapDistance = std::abs(distance - mRadius);
	auto invertedDirection = -mDirection;
	this->setPosition(invertedDirection.normalized() * snapDistance);
}
