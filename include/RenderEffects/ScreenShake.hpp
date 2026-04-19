#pragma once
#include "RenderEffect.hpp"

namespace pyramidnight {
	class ScreenShake : public RenderEffect {
		public:
			// shake the window view for duration and power
			ScreenShake(float duration, float power);
			void Update(const Context& context) override;
			
			
			float Power;
		private:
			bool         mIsOriginSet;
			sf::Vector2f mViewOrigin;
			bool         mIsShaking;
	};
}