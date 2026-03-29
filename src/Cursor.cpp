#include <algorithm>
#include "Cursor.hpp"

namespace fknd {
	
	Cursor::Cursor(sf::Font& font) : mFont(font) {
		mEntryIndex = 0;
		auto cursorSize =  sf::Vector2f({});
		cursorSize.x =	mFont.getGlyph('?', CUR_FONT_SZ, false).bounds.size.x;
		cursorSize.y =	mFont.getGlyph('?', CUR_FONT_SZ, false).bounds.size.y;
	
		setSize(cursorSize);
		setFillColor(CUR_FILL_COL);
		setOutlineColor(CUR_OUTLINE_COL);
		setOutlineThickness(CUR_OUTLINE_SZ);
	}
	
	//TODO fix cursor pos
	void Cursor::Update(Input action) {
		switch (action)
		{
			case Input::LEFT:
				if (mEntryIndex > 0) {
					move({-CUR_MV_OFFSET,0});
					mEntryIndex = std::clamp(--mEntryIndex, (size_t)0, (size_t)2);
				}
				break;
			case Input::RIGHT:
	
				if (mEntryIndex < 2) {
					move({CUR_MV_OFFSET,0});
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
		setOutlineColor(sf::Color::Transparent);
		return true;
	}

	//TODO fix first down push
	void Cursor::ChangeChar(Input action) {
		char selected = SelectChar(action);
		std::string str = mEntryTxt->getString();
		
		str[mEntryIndex] = selected;
		mEntryTxt->setString(str);
	}
	
	//TODO fix first down push
	char Cursor::SelectChar(Input action) {
		static int index = -1;
		char selected = 'A';
		const int max = CUR_CHAR_SET.size();
	
		switch (action)	{
			case Input::UP:
				index =  (index + 1) % max;
				selected = CUR_CHAR_SET[index];
				break;
			case Input::DOWN:
				index = (index - 1 + max) % max;
				selected = CUR_CHAR_SET[index];
				break;
			default:
				break;
		}
		return selected;
	}

}
