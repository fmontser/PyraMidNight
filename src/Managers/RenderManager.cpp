#include "RenderManager.hpp"

namespace pyramidnight {
	
	RenderManager::RenderManager() :
		mWindow(sf::VideoMode(RNDR_RESOLUTION),
		"PyraMidNight",
		sf::Style::Titlebar | sf::Style::Close) {
			mWindow.setFramerateLimit(RNDR_FRAME_LIMIT);
	}
	
	void RenderManager::Init() { instance(); }

	void RenderManager::RenderFrame(std::vector<std::shared_ptr<sf::Drawable>>& drawables) {
		auto& window = instance().mWindow;

		window.clear();
		for (const auto& drw : drawables)
			window.draw(*drw);
		window.display();
	}
	
	sf::Time& RenderManager::GetDeltaTime() { 
		auto& deltaTime = instance().mDeltaTime;
		auto& clock = instance().mClock;
		
		deltaTime = clock.restart();
		return deltaTime;
	}
	
	sf::RenderWindow& RenderManager::GetWindow() { return instance().mWindow; }

}	
