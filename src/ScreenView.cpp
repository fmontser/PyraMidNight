#include "ScreenView.hpp"

ScreenView::ScreenView() { enabled = false; }

void ScreenView::Show() { enabled = true; }
void ScreenView::Hide() { enabled = false; }

const std::vector<std::shared_ptr<sf::Drawable>>&
ScreenView::GetDrawables() const { return mDrawables; }
