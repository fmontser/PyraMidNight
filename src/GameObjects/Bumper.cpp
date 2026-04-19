#include <algorithm>
#include <cmath>
#include "Bumper.hpp"
#include "Ball.hpp"
#include "PowerUp.hpp"
#include "HolyMisile.hpp"
#include "RenderManager.hpp"
#include "Flash.hpp"

namespace pyramidnight {

	Bumper::Bumper(const sf::Texture& texture, const sf::Texture& magicTexture) :
		sf::Sprite(texture), mMagicTexture(magicTexture) {
		CollidableType = ICollidable::Type::BUMPER;
		IsDynamic = true;
		mSpeed = BMPR_INIT_SPEED;
		mSpeedPenalty = 1.0f;
		mSpeedPenaltyTime = 0.0f;
		mIsMagicEnabled = false;
		mMagicDuration = 0.0f;
		mMagicFireRate = 0.0f;
		mTint = getColor();
	}

	ICollidable::Info Bumper::OnCollision(ICollidable &collider) { 
		switch (collider.CollidableType) {
			case ICollidable::Type::BALL: return OnBallCollision(collider);
			case ICollidable::Type::POWER_UP: return OnPowerUpCollision(collider);
			default: break;
		}
		return { CollidableType, false, 0, std::nullopt };
	}

	ICollidable::Info Bumper::OnBallCollision(ICollidable &collider) {
		auto& ball = static_cast<Ball&>(collider);
		auto cpos = GetCollisionPoint(ball.getGlobalBounds());
		if (cpos != std::nullopt) {
			return { CollidableType, false, 0, cpos };
		}
		return { CollidableType, false, 0, std::nullopt };
	}

	ICollidable::Info Bumper::OnPowerUpCollision(ICollidable &collider) {
		auto& pup = static_cast<PowerUp&>(collider);
		auto cpos = GetCollisionPoint(pup.getGlobalBounds());
		if (cpos != std::nullopt) {
			switch(pup.PowerUpType) {
				case PowerUp::Type::GHOST: {SetSpeedPenalty(PWRUP_GHOST_PENALTY_MOD, PWRUP_GHOST_PENALTY_TIME); break;}
				case PowerUp::Type::MAGIC: { EnableMagic(PWRUP_MAGIC_DURATION); break;} //TODO new outline effect
				default: break;
			}
			return { CollidableType, false, 0, cpos };
		}
		return { CollidableType, false, 0, std::nullopt };
	}


	void Bumper::Update(BumperUpdate update) {
		if (update.holdLeft || update.holdRight)
			Move(update);
		if (mIsMagicEnabled)
			FireMagic(update);
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
	
		mSpeedPenaltyTime -= update.deltaTime.asSeconds();
		if (mSpeedPenaltyTime <= 0) {
			mSpeedPenalty = 1.0;
			mSpeedPenaltyTime = 0.0f;
		}

		mSpeed *= mSpeedPenalty;
		position.x += direction * mSpeed * update.deltaTime.asSeconds();
		position.x = std::clamp(position.x, BMPR_MV_LIMIT_L, BMPR_MV_LIMIT_R);
		this->setPosition(position);
		mSpeed = BMPR_INIT_SPEED * mSpeedPenalty;
	}

	void Bumper::EnablePenaltyFlashEffect(float duration) {
		RenderManager::DisplayEffect(std::make_unique<Flash>(
			duration, EFF_FLASH_GHOST_LAPSE, EFF_FLASH_GHOST_ATTACK_COLOR, mTint, shared_from_this()));
	}

	void Bumper::EnableMagic(float duration) {
		mIsMagicEnabled = true;
		mMagicDuration = std::abs(duration);
	}

	void Bumper::FireMagic(BumperUpdate& update) {
		mMagicDuration -= update.deltaTime.asSeconds();
		mMagicFireRate += update.deltaTime.asSeconds();
		if (mMagicDuration <= 0) {
			mIsMagicEnabled = false;
			mMagicDuration = 0.0f;
		}

		if (mMagicFireRate > PWRUP_MAGIC_FIRERATE && update.action) {
			mMagicFireRate = 0.0f;

			auto misile =  std::make_shared<HolyMisile>(mMagicTexture);
			misile->Spawn(GetBumperFirePosition(), update.drawableVector, update.coldetVector);
		}
	}

	void Bumper::SetSpeedPenalty(float penalty, float duration) {
		if (mSpeedPenaltyTime <= 0) {
			EnablePenaltyFlashEffect(duration);
			mSpeedPenalty = penalty;
			mSpeedPenaltyTime = duration;
		}
	}
	
	std::optional<sf::Vector2f> Bumper::GetCollisionPoint(const sf::FloatRect &rect) {
		if (auto overlap = getGlobalBounds().findIntersection(rect))
			return overlap->position + (overlap->size / 2.0f);
		return std::nullopt;
	}

	sf::Vector2f Bumper::GetBumperFirePosition() {
		auto pos = getPosition();
		pos += {getGlobalBounds().size.x / 2.0f, 0.0f};
		return pos;
	}
}