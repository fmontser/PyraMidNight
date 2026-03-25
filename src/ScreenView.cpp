#include "ScreenView.hpp"

//TODO check mDeltaTime init...
ScreenView::ScreenView(sf::RenderWindow& window, sf::Time& deltaTime) :
	mWindow(window),
	mDeltaTime(deltaTime) {
		enabled = false;
}

void ScreenView::Show() { enabled = true; }

void ScreenView::Hide() { enabled = false; }

void ScreenView::Draw() {
	if (enabled) {
		for (const auto& dPtr : mDrawables)
			mWindow.draw(*dPtr);
	}
}
