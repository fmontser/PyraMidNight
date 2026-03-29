#include "RenderManager.hpp"

namespace fknd {
	
	//TODO remove hardcoded
	RenderManager::RenderManager() :
		mWindow(sf::VideoMode({640, 896}),
		"FranKanoid",
		sf::Style::Titlebar | sf::Style::Close) {
			mWindow.setFramerateLimit(60);
	}
	
	void RenderManager::RenderFrame(ScreenView& screenView) {
		mWindow.clear();
	
		for (const auto& drw : screenView.GetDrawables())
			mWindow.draw(*drw);
	
		mWindow.display();
	}
	
	sf::Time& RenderManager::GetDeltaTime() { 
		mDeltaTime = mClock.restart();
		return mDeltaTime;
	}
	
	sf::RenderWindow& RenderManager::GetWindow() { return mWindow; }

}	
