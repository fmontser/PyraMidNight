#include <algorithm>
#include "Cursor.hpp"
#include "AudioManager.hpp"
#include "RenderManager.hpp"

namespace pyramidnight {
	
	Cursor::Cursor(sf::Font& font) : mFont(font) {
		mNameIndex = 0;
		mIsEnabled = false;
		auto cursorSize =  sf::Vector2f({});
		cursorSize.x =	mFont.getGlyph('?', CUR_FONT_SZ, false).bounds.size.x;
		cursorSize.y =	mFont.getGlyph('?', CUR_FONT_SZ, false).bounds.size.y;
	
		setSize(cursorSize);
		setFillColor(CUR_FILL_COL);
		setOutlineColor(sf::Color::Transparent);
		setOutlineThickness(CUR_OUTLINE_SZ);
	}
	

	bool Cursor::Update(const CursorUpdate& update) {
		if (update.nameText.get() == nullptr)
			return true;
		else if (!mIsEnabled)
			SetPosition(*update.nameText);
		if (update.left) {
			if (mNameIndex > 0) {
				move({-CUR_MV_OFFSET,0});
				--mNameIndex;
				mNameIndex = std::clamp<size_t>(mNameIndex, 0, 2);
				SelectChar(update);
			}
		} else if (update.right) {
			if (mNameIndex < 2) {
				move({CUR_MV_OFFSET,0});
				++mNameIndex;
				mNameIndex = std::clamp<size_t>(mNameIndex, 0, 2);
				SelectChar(update);
			}
		} else if (update.up || update.down) 
			ChangeChar(update);
		else if (update.action) {
			setOutlineColor(sf::Color::Transparent);
			return false;
		}
		Blink();
		return true;
	}

	void Cursor::SetPosition(const sf::Text& nameText) {
		auto offset = sf::Vector2f({5.0f, -30.0f});
		move(nameText.getGlobalBounds().position + offset);
		mIsEnabled = true;
	}
	

	//TODO move blink to render manager??
	void Cursor::Blink() {
		static float timeElapsed = 0;
		static sf::Color color = sf::Color::Transparent;
		timeElapsed += RenderManager::GetDeltaTime().asSeconds();

		if (timeElapsed >= CUR_BLINK_TIME_SEC) {
			color = color == sf::Color::Transparent ? CUR_OUTLINE_COL : sf::Color::Transparent;
			setOutlineColor(color);
			timeElapsed -= CUR_BLINK_TIME_SEC;
		}
	}

	void Cursor::ChangeChar(const CursorUpdate& update) {
		char selected = SelectChar(update);
		std::string str = (*update.nameText).getString();
		str[mNameIndex] = selected;
		(*update.nameText).setString(str);
		AudioManager::Play({PATH_AUD_CURSOR, VOL_AUD_CURSOR, PolySound::Type::SFX, false});
	}
	
	char Cursor::SelectChar(const CursorUpdate& update) {
		static int index = 0;
		char selected = 'A';
		const int max = CUR_CHAR_SET.size();

		if (update.up) {
			index =  (index + 1) % max;
			selected = CUR_CHAR_SET[index];
		}
		else if (update.down) {
			index = (index - 1 + max) % max;
			selected = CUR_CHAR_SET[index];
		} else
			index = 0;
		AudioManager::Play({PATH_AUD_CURSOR, VOL_AUD_CURSOR, PolySound::Type::SFX, false});
		return selected;
	}
}
