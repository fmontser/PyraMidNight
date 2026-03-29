#include "ScreenView.hpp"

namespace fknd {
	
	ScreenView::ScreenView() {}
	
	std::vector<std::shared_ptr<sf::Drawable>>&
	ScreenView::GetDrawables() { return mDrawables; }

}
