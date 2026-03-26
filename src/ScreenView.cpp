#include "ScreenView.hpp"

ScreenView::ScreenView() {}

const std::vector<std::shared_ptr<sf::Drawable>>&
ScreenView::GetDrawables() const { return mDrawables; }
