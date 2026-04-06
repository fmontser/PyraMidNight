#pragma once
#include <SFML/Graphics.hpp>

namespace pyramidnight {

	class RenderEffect {
		public:
			virtual void Update() = 0;
		
			bool Disposable;
			
		protected:
			float mDuration;
			bool  mLoop;
			
			RenderEffect(float durationSeconds);
	};
}