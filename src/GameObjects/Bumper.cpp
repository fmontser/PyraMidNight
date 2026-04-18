#include <algorithm>
#include <cmath>
#include "Bumper.hpp"
#include "Ball.hpp"
#include "PowerUp.hpp"
#include "RenderManager.hpp"
#include "Flash.hpp"

namespace pyramidnight {
	
	Bumper::Bumper(const sf::Texture& texture, const sf::Texture& magicTexture) :
		sf::Sprite(texture), mMagicTexture(magicTexture) {
		mSpeed = BMPR_INIT_SPEED;
		mSpeedPenalty = 1.0f;
		mIsMagicEnabled = false;
		mAnimationDelta = 0.0f;
		mAnimationRect = {{0,0},{32,32}};
		mMagicDuration = 0.0f;
		mMagicFireRate = 0.0f;
		CollidableType = ICollidable::Type::BUMPER;
	}

	ICollidable::Info Bumper::OnCollision(ICollidable &collider) { 
		if (collider.CollidableType == ICollidable::Type::BALL) {
			auto& ball = static_cast<Ball&>(collider);
			auto cpos = ball.GetCollisionPoint(getGlobalBounds());
			if (cpos != std::nullopt) {
				ball.Bounce(*this);
				ball.ApplyBumperMod(*this);
			}
		}
		return { CollidableType, false, 0, std::nullopt };
	}

	std::optional<sf::Vector2f> Bumper::GetCollisionPoint(const sf::FloatRect &rect) {
		if (auto overlap = getGlobalBounds().findIntersection(rect))
			return overlap->position + (overlap->size / 2.0f);
		return std::nullopt;
	}

	void Bumper::Update(BumperUpdate update) {
		if (update.holdLeft || update.holdRight)
			Move(update);

		if (mIsMagicEnabled)
			FireMagic(update.action, update.deltaTime, update.drawables);

		////TODO temp test
		for (auto& misile : mMisileVector) {
			auto position =  misile->getPosition();
			position.y -= 200.0f * update.deltaTime.asSeconds(); //TODO hardcoded
			misile->setPosition(position);
			AnimateFrame(*misile,update.deltaTime);
		}
	}

	void Bumper::Move(BumperUpdate update) {
		sf::Vector2 position = this->getPosition();
		float direction;
		if (update.holdLeft)
			direction = -1.0f;
		else if (update.holdRight)
			direction = 1.0f;
		if (update.fine && !update.coarse)
			mSpeed *= BMPR_FINE_SPEED_MOD;
		else if (!update.fine && update.coarse)
			mSpeed *= BMPR_COARSE_SPEED_MOD;
	
		mSpeed *= mSpeedPenalty;
		position.x += direction * mSpeed * update.deltaTime.asSeconds();
		position.x = std::clamp(position.x, BMPR_MV_LIMIT_L, BMPR_MV_LIMIT_R);
		this->setPosition(position);
		mSpeed = BMPR_INIT_SPEED * mSpeedPenalty;
	}

	void Bumper::EnablePenaltyFlashEffect(float duration) {
		RenderManager::DisplayEffect(std::make_unique<Flash>(
			duration, EFF_FLASH_GHOST_LAPSE, EFF_FLASH_GHOST_ATTACK_COLOR, getColor(), shared_from_this()));
	}

	void Bumper::EnableMagic(float duration) {
		mIsMagicEnabled = true;
		mMagicDuration = std::abs(duration);
	}

	void Bumper::FireMagic(bool action, const sf::Time& deltaTime,
		std::vector<std::shared_ptr<sf::Drawable>>& drawables) {
		mMagicDuration -= deltaTime.asSeconds();
		mMagicFireRate += deltaTime.asSeconds();
		if (mMagicDuration <= 0) {
			mIsMagicEnabled = false;
			mMagicDuration = 0.0f;
		}

		if (mMagicFireRate > PWRUP_MAGIC_FIRERATE && action) {
			mMagicFireRate = 0.0f;

			auto misile =  std::make_shared<sf::Sprite>(mMagicTexture);
			misile->setScale({1, -1});
			misile->setPosition(getPosition());
			misile->setTextureRect(mAnimationRect);
			mMisileVector.push_back(misile);
			drawables.push_back(misile);
			//TODO limpiar los drawables? al crear el objeto que se eliminen duera de la zona de juego
		}
	}

	//TODO test delete
	void Bumper::AnimateFrame(sf::Sprite& sprite, const sf::Time &deltaTime) {
		mAnimationDelta += deltaTime.asSeconds();
		if (mAnimationDelta >= ANI_MAGIC_FRAMERATE) {
			size_t newFrameX = mAnimationRect.position.x + sprite.getGlobalBounds().size.x;
			
			if (newFrameX >= 96) //TODO hardcoded
				newFrameX = 0;
			mAnimationRect.position.x = newFrameX;
			sprite.setTextureRect(mAnimationRect);
			mAnimationDelta = 0;
		}
	}

	void Bumper::SetSpeedPenalty(float penalty) { mSpeedPenalty = penalty;	}
}