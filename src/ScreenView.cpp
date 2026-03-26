#include "ScreenView.hpp"

ScreenView::ScreenView() {}

std::vector<std::shared_ptr<sf::Drawable>>&
ScreenView::GetDrawables() { return mDrawables; }
