#include "RenderManager.hpp"

//TODO remove hardcoded
RenderManager::RenderManager(uint16_t width, uint16_t height) :
	mWindow(sf::VideoMode(width, height), "FranKanoid") {}

void RenderManager::RenderFrame(ScreenView& screenView) {
	mDeltaTime = mClock.restart();
	mWindow.clear();

	for (const auto& drw : screenView.GetDrawables())
		mWindow.draw(*drw);

	mWindow.display();
}

sf::Time RenderManager::GetDeltaTime() const { return sf::Time(); }
sf::RenderWindow& RenderManager::GetWindow() { return mWindow; }

