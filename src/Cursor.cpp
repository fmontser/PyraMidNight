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
	
	void Cursor::Update(Input action) {

		switch (action)
		{
			case Input::LEFT:
				if (mEntryIndex > 0) {
					move({-CUR_MV_OFFSET,0});
					mEntryIndex = std::clamp(--mEntryIndex, (size_t)0, (size_t)2);
					SelectChar(Input::LEFT);
				}
				break;
			case Input::RIGHT:
	
				if (mEntryIndex < 2) {
					move({CUR_MV_OFFSET,0});
					mEntryIndex = std::clamp(++mEntryIndex, (size_t)0, (size_t)2);
					SelectChar(Input::RIGHT);
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
		auto offset = sf::Vector2f({5.0f, -30.0f});
		move(mEntryTxt->getGlobalBounds().position + offset);
	}
	
	bool Cursor::Accept(std::string* gameEntryName) {
		if (gameEntryName != nullptr)
			*gameEntryName = mEntryTxt->getString();
		setOutlineColor(sf::Color::Transparent);
		return true;
	}

	void Cursor::Blink() {
		static size_t frameCount = 0;
		if (frameCount++ < RNDR_FRAME_LIMIT / 2)
			setOutlineColor(sf::Color::Transparent);
		else
			setOutlineColor(sf::Color::Green);
		if (frameCount == RNDR_FRAME_LIMIT)
			frameCount = 0;
	}

	void Cursor::ChangeChar(Input action) {
		char selected = SelectChar(action);
		std::string str = mEntryTxt->getString();
		
		str[mEntryIndex] = selected;
		mEntryTxt->setString(str);
	}
	
	char Cursor::SelectChar(Input action) {
		static int index = 0;
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
				index = 0;
				break;
		}
		return selected;
	}

}
