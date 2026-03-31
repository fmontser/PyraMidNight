#include "ScreenView.hpp"

namespace fknd {
	
	ScreenView::ScreenView() {}
	
	std::vector<std::shared_ptr<sf::Drawable>>&
	ScreenView::GetDrawables() { return mDrawables; }

	void ScreenView::Pause() {
		if (mClock.isRunning())
			mClock.stop();
	}

	void ScreenView::Resume() {
		if (!mClock.isRunning())
			mClock.start();
	}
}
