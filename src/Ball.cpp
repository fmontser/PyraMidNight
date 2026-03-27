#include "Ball.hpp"
#include <algorithm>

Ball::Ball(const sf::Texture& texture) : sf::Sprite(texture) {
	mSpeed = 200;
	mDirection = {-1, -1};
	mRadius = 32.0f;
	ResetPos({256, 832});
}

void Ball::Launch() {
	mState = State::PLAYING;
}

void Ball::ResetPos(const sf::Vector2f &bumperPos) {
	sf::Vector2f offset({48,-32});
	auto newPos = bumperPos + offset;
	this->setPosition(newPos);
	mState = State::DOCKED;
}

void Ball::Update(const sf::Vector2f &bumperPos, sf::Time& deltaTime) {
	switch (mState)	{
		case State::PLAYING: Move(deltaTime); break;
		case State::DOCKED: ResetPos(bumperPos); break;
		default: break;
	}
}

void Ball::Bounce(sf::Rect<float> rect) {
	//TODO
}

const Ball::State &Ball::GetState() const { return mState; }
const sf::Vector2f &Ball::GetPostion() const { return this->getPosition(); }
const float Ball::GetRadius() const { return mRadius; }

//TODO hardcoded values...
void Ball::Move(sf::Time& deltaTime) {
	sf::Vector2f position = this->getPosition();
	position.x += mDirection.x * mSpeed * deltaTime.asSeconds();
	position.y += mDirection.y * mSpeed * deltaTime.asSeconds();
	position.x = std::clamp(position.x, 32.0f, 576.0f);
	position.y = std::clamp(position.y, 32.0f, 896.0f);
	this->setPosition(position);
}
