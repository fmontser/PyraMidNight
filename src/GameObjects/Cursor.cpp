#include <algorithm>
#include "Cursor.hpp"
#include "AudioManager.hpp"

namespace pyramidnight {
	
	Cursor::Cursor(sf::Font& font, sf::Clock& clock) : mFont(font), mClock(clock) {
		mEntryTxt = nullptr;
		mEntryIndex = 0;
		auto cursorSize =  sf::Vector2f({});
		cursorSize.x =	mFont.getGlyph('?', CUR_FONT_SZ, false).bounds.size.x;
		cursorSize.y =	mFont.getGlyph('?', CUR_FONT_SZ, false).bounds.size.y;
	
		setSize(cursorSize);
		setFillColor(CUR_FILL_COL);
		setOutlineColor(sf::Color::Transparent);
		setOutlineThickness(CUR_OUTLINE_SZ);
	}
	
	void Cursor::Update(Input action) {
		if (mEntryTxt == nullptr)
			return;
		switch (action)
		{
			case Input::LEFT:
				if (mEntryIndex > 0) {
					move({-CUR_MV_OFFSET,0});
					--mEntryIndex;
					mEntryIndex = std::clamp<size_t>(mEntryIndex, 0, 2);
					SelectChar(Input::LEFT);
				}
				break;
			case Input::RIGHT:
				if (mEntryIndex < 2) {
					move({CUR_MV_OFFSET,0});
					++mEntryIndex;
					mEntryIndex = std::clamp<size_t>(mEntryIndex, 0, 2);
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
	
	bool Cursor::SetEntry(sf::Text* entry) {
		mEntryTxt = entry;
		auto offset = sf::Vector2f({5.0f, -30.0f});
		move(mEntryTxt->getGlobalBounds().position + offset);
		return true;
	}
	
	bool Cursor::Accept(std::string* gameEntryName) {
		if (gameEntryName != nullptr)
			*gameEntryName = mEntryTxt->getString();
		setOutlineColor(sf::Color::Transparent);
		return true;
	}

	void Cursor::Blink() {
		if (mEntryTxt == nullptr)
			return;
		static float timeElapsed = 0;
		static sf::Color color = sf::Color::Transparent;
		timeElapsed += mClock.restart().asSeconds();

		if (timeElapsed >= CUR_BLINK_TIME_SEC) {
			color = color == sf::Color::Transparent ? CUR_OUTLINE_COL : sf::Color::Transparent;
			setOutlineColor(color);
			timeElapsed -= CUR_BLINK_TIME_SEC;
		}
	}

	void Cursor::ChangeChar(Input action) {
		char selected = SelectChar(action);
		std::string str = mEntryTxt->getString();
		
		str[mEntryIndex] = selected;
		mEntryTxt->setString(str);
		AudioManager::Play(PATH_AUD_CURSOR, VOL_AUD_CURSOR, false);
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
		AudioManager::Play(PATH_AUD_CURSOR, VOL_AUD_CURSOR, false);
		return selected;
	}

}
