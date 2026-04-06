#pragma once
#include "RenderEffect.hpp"

namespace pyramidnight {
	class ScreenShake : public RenderEffect {
		public:
			ScreenShake(float duration, float power);
			void Update();
			
			float Power;
	};
}