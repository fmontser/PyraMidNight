#include <algorithm>
#include "Cursor.hpp"

constexpr std::string_view CHARSET_STR = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

Cursor::Cursor(sf::Font& font) : mFont(font) {
	mEntryIndex = 0;
	auto cursorSize =  sf::Vector2f({});
	cursorSize.x =	mFont.getGlyph('?', 48.0f, false).bounds.size.x;
	cursorSize.y =	mFont.getGlyph('?', 48.0f, false).bounds.size.y;

	setSize(cursorSize);
	setFillColor({0, 0, 0, 0});
	setOutlineColor({0, 255, 0, 255});
	setOutlineThickness(2);
}

//TODO hardcoded data...
void Cursor::Update(Input action) {
	switch (action)
	{
		case Input::LEFT:
			if (mEntryIndex > 0) {
				move({-30,0});
				mEntryIndex = std::clamp(--mEntryIndex, (size_t)0, (size_t)2);
			}
			break;
		case Input::RIGHT:

			if (mEntryIndex < 2) {
				move({30,0});
				mEntryIndex = std::clamp(++mEntryIndex, (size_t)0, (size_t)2);
			}
			break;
		case Input::UP:
			ChangeChar(Input::UP);
			break;
		case Input::DOWN:
			ChangeChar(Input::DOWN);
			break;
		default:
			break;
	}
}

void Cursor::SetEntry(std::shared_ptr<sf::Text> &entry) { 
	mEntryTxt = entry;
	move(mEntryTxt->getGlobalBounds().position);
}

//TODO refactor ranking system
bool Cursor::Accept(std::string* gameEntryName) {
	if (gameEntryName != nullptr)
		*gameEntryName = mEntryTxt->getString();
	setOutlineColor({0, 0, 0, 0});
	return true;
}

void Cursor::ChangeChar(Input action) {
	char selected = SelectChar(action);
	std::string str = mEntryTxt->getString();
	
	str[mEntryIndex] = selected;
	mEntryTxt->setString(str);
}

char Cursor::SelectChar(Input action) {
	static int index = -1;
	char selected = 'A';
	const int max = CHARSET_STR.size();

	switch (action)	{
		case Input::UP:
			index =  (index + 1) % max;
			selected = CHARSET_STR[index];
			break;
		case Input::DOWN:
			index = (index - 1 + max) % max;
			selected = CHARSET_STR[index];
			break;
		default:
			break;
	}
	return selected;
}
