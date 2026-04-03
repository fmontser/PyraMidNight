#include "RenderManager.hpp"

namespace fknd {
	
	RenderManager::RenderManager() :
		mWindow(sf::VideoMode(RNDR_RESOLUTION),
		"PyraMidNight",
		sf::Style::Titlebar | sf::Style::Close) {
			mWindow.setFramerateLimit(RNDR_FRAME_LIMIT);
	}
	
	void RenderManager::RenderFrame(
		std::vector<std::shared_ptr<sf::Drawable>>& drawables) {
		mWindow.clear();
	
		for (const auto& drw : drawables)
			mWindow.draw(*drw);
	
		mWindow.display();
	}
	
	sf::Time& RenderManager::GetDeltaTime() { 
		mDeltaTime = mClock.restart();
		return mDeltaTime;
	}
	
	sf::RenderWindow& RenderManager::GetWindow() { return mWindow; }

}	
