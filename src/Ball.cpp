#include <algorithm>
#include <cmath>
#include "Ball.hpp"


Ball::Ball(const sf::Texture& texture) : sf::Sprite(texture) {
	mSpeed = fkd::BALL_INIT_SPEED;
	mDirection = fkd::BALL_INIT_DIR;
	mRadius = texture.getSize().x / 2;
	setOrigin({mRadius,mRadius});
	ResetPos(fkd::BALL_INIT_POS);
}

void Ball::Launch() {
	if (mState == State::DOCKED)
		mState = State::PLAYING;
}

void Ball::ResetPos(const sf::Vector2f &bumperPos) {
	auto newPos = bumperPos + fkd::BALL_DOCKED_OFFSET;
	setPosition(newPos);
	mDirection = fkd::BALL_INIT_DIR;
	mState = State::DOCKED;
}

void Ball::Update(const sf::Vector2f &bumperPos, const sf::Time& deltaTime) {
	switch (mState) {
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

//TODO add formula as comment?
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
