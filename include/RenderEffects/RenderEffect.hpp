#pragma once
#include <SFML/Graphics.hpp>

namespace pyramidnight {

	class RenderEffect {
		public:
			virtual void Update() = 0;
		
			float Duration;
		
		protected:
			RenderEffect(float durationSeconds);
	};
}