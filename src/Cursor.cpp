#include "Cursor.hpp"

constexpr std::string_view ABC_STR = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

Cursor::Cursor(sf::Font& font) : mFont(font) {
	auto cursorSize =  sf::Vector2f({});
	cursorSize.x =	mFont.getGlyph('?', 48.0f, false).bounds.size.x;
	cursorSize.y =	mFont.getGlyph('?', 48.0f, false).bounds.size.y;

	setSize(cursorSize);
	setFillColor({0, 0, 0, 0});
	setOutlineColor({0, 255, 0, 255});
	setOutlineThickness(2);
}

void Cursor::Control(Action action) {
	switch (action)
	{
		case Action::LEFT:
			move({-30,0});
			break;
		case Action::RIGTH:
			move({30,0});
			break;
		case Action::UP:
			move({0,-30});
			break;
		case Action::DOWN:
			move({0,30});
			break;
		default:
			break;
	}
}

void Cursor::SetEntry(std::shared_ptr<sf::Text> &entry) {
	//TODO
}

bool Cursor::IsNameSet() {
	return false;
}
