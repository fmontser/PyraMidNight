#include "ScreenView.hpp"

namespace pyramidnight {
	
	std::vector<std::shared_ptr<sf::Drawable>>&
	ScreenView::GetDrawables() { return mDrawables; }
}
