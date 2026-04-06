#pragma once
#include <SFML/Graphics.hpp>
#include "ScreenView.hpp"
#include "Common.hpp"

namespace pyramidnight {
	
	class RenderManager {
		public:
			static void Init();
			static void RenderFrame(std::vector<std::shared_ptr<sf::Drawable>>& drawables);
			static sf::Time& GetDeltaTime();
			static sf::RenderWindow& GetWindow();
			
		private:
			RenderManager();
			RenderManager(const RenderManager& src) = delete;
			RenderManager& operator=(const RenderManager& src) = delete;

			sf::RenderWindow mWindow;
			sf::Clock        mClock;
			sf::Time         mDeltaTime;

			static RenderManager& instance() {
				static RenderManager inst;
				return inst;
			}
	};

}