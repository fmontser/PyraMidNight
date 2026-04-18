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
		mIsMagicEnabled = false;
		mMagicDuration = 0.0f;
		mMagicFireRate = 0.0f;
	}

	ICollidable::Info Bumper::OnCollision(ICollidable &collider) { 
		switch (collider.CollidableType) {
			case ICollidable::Type::BALL: return OnBallCollision(collider);
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


	void Bumper::Update(BumperUpdate update) {
		if (update.holdLeft || update.holdRight)
			Move(update);
		if (mIsMagicEnabled)
			FireMagic(update.action, update.deltaTime, update.mMisileVector, update.drawables);
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
		std::vector<std::shared_ptr<Misile>>& misiles,
		std::vector<std::shared_ptr<sf::Drawable>>& drawables) {

		mMagicDuration -= deltaTime.asSeconds();
		mMagicFireRate += deltaTime.asSeconds();
		if (mMagicDuration <= 0) {
			mIsMagicEnabled = false;
			mMagicDuration = 0.0f;
		}

		if (mMagicFireRate > PWRUP_MAGIC_FIRERATE && action) {
			mMagicFireRate = 0.0f;

			//TODO projectiles to spawner!!s
			auto misile =  std::make_shared<HolyMisile>(mMagicTexture);
			misile->setTextureRect({{0,0},{32,32}});
			misile->Spawn(GetBumperFirePosition(), drawables);
			misiles.push_back(misile);
		}
	}

	void Bumper::SetSpeedPenalty(float penalty) { mSpeedPenalty = penalty;	}
	

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