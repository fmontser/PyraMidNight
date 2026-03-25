#include "ScreenView.hpp"

ScreenView::ScreenView(sf::RenderWindow& window) : mWindow(window) {
	enabled = false;
}

void ScreenView::Show() { enabled =  true; }

void ScreenView::Hide() { enabled = false; }

void ScreenView::Draw() {
	if (enabled) {
		for (const auto& dPtr : mDrawables)
			mWindow.draw(*dPtr);
	}
}
