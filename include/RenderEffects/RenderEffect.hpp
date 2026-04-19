#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace pyramidnight {

	class RenderEffect {
		public:
			struct Context {
				const sf::Time&   deltaTime;
				sf::RenderWindow& window;
			};

			bool Disposable;
			
			virtual void Update(const Context& context) = 0;
			virtual ~RenderEffect() = default;
		
		protected:
			RenderEffect(float durationSeconds);
			
			float mDuration;
			bool  mLoop;
	};
}