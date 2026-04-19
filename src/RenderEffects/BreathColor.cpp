#include <cmath>
#include "BreathColor.hpp"


namespace pyramidnight {

	BreathColor::BreathColor(float duration, float lapse, sf::Color breath, sf::Color original,
		const std::weak_ptr<sf::Sprite>& sprite) :
			RenderEffect(duration) , mSprite(sprite) {
				Lapse = lapse;
				mElapsedTime = 0.0f;
				mBreathing = false;
				mBreathColor = breath;
				mOriginalColor = original;
	}

	void BreathColor::Update(const Context& context) {
		auto obj = mSprite.lock();
		if (!obj) {
			Disposable = true;
			return;
		}

		mElapsedTime += context.deltaTime.asSeconds();
		mDuration -= context.deltaTime.asSeconds();

		// Finalizar el efecto y restaurar color original
		if (!mLoop && mDuration <= 0.0f) {
			obj->setColor(mOriginalColor);
			Disposable = true;
			return;
		}

		// Calculamos el factor de respiración (oscila entre 0.0 y 1.0)
		// Usamos 'Lapse' como la velocidad: a menor Lapse, más rápido respira.
		float speed = 2.0f * 3.14159f / Lapse; 
		float factor = (std::sin(mElapsedTime * speed) + 1.0f) / 2.0f;

		// Interpolación lineal (Lerp) entre mOriginalColor y mBreathColor (Verde)
		sf::Color currentColor;
		currentColor.r = static_cast<uint8_t>(mOriginalColor.r + (mBreathColor.r - mOriginalColor.r) * factor);
		currentColor.g = static_cast<uint8_t>(mOriginalColor.g + (mBreathColor.g - mOriginalColor.g) * factor);
		currentColor.b = static_cast<uint8_t>(mOriginalColor.b + (mBreathColor.b - mOriginalColor.b) * factor);
		currentColor.a = static_cast<uint8_t>(mOriginalColor.a + (mBreathColor.a - mOriginalColor.a) * factor);

		obj->setColor(currentColor);
	}
}