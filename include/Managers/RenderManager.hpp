#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "RenderEffect.hpp"
#include "Common.hpp"

namespace pyramidnight {
	
	class RenderManager {
		public:
			static void Init();
			static void Update(std::vector<std::shared_ptr<sf::Drawable>> &drawables);
			static void DisplayEffect(std::unique_ptr<RenderEffect> effect);
			static sf::Time& GetDeltaTime();
			static sf::RenderWindow &GetWindow();
			
			private:
			RenderManager();
			RenderManager(const RenderManager& src) = delete;
			RenderManager& operator=(const RenderManager& src) = delete;
			
			sf::RenderWindow          mWindow;
			sf::Clock                 mClock;
			sf::Time                  mDeltaTime;
			std::vector<std::unique_ptr<RenderEffect>> mRenderEffects;
			
			
			void Draw(std::vector<std::shared_ptr<sf::Drawable>> &drawables);
			void DrawEffects();

			static RenderManager& instance() {
				static RenderManager inst;
				return inst;
			}
	};

}