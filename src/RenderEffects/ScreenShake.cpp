#include "ScreenShake.hpp"
#include "RenderManager.hpp"

namespace pyramidnight {
	
	ScreenShake::ScreenShake(float duration, float power) : RenderEffect(duration) {
		Power = power; //TODO check negative values.
	}

	void ScreenShake::Update() {
		static auto&        window = RenderManager::GetWindow();
		static auto         deltaTime = RenderManager::GetDeltaTime();
		static auto         view = window.getView();
		static sf::Vector2f origin = view.getCenter();
		static bool         isShaking = false;

		if (!isShaking && Duration > 0.0f)
			isShaking = true;
		if (Duration > 0.0f) {
			Duration -= deltaTime.asSeconds();
			float offsetX = ((float)rand() / RAND_MAX * 2.f - 1.f) * Power;
			float offsetY = ((float)rand() / RAND_MAX * 2.f - 1.f) * Power;
			view.setCenter({origin.x + offsetX, origin.y + offsetY});
		}
		if (isShaking && Duration <= 0.0f) {
			view.setCenter(origin);
			isShaking = false;
		}
		window.setView(view);
	}
}