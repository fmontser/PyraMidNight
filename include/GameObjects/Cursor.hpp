#pragma once
#include <SFML/Graphics.hpp>
#include "Common.hpp"

namespace pyramidnight {
	
	class Cursor : public sf::RectangleShape {
		public:
			struct CursorUpdate {
				bool left;
				bool right;
				bool up;
				bool down;
				bool action;
				std::shared_ptr<sf::Text> nameText;
			};

			Cursor(sf::Font& font);
	
			bool Update(const CursorUpdate& update);
			
			private:
			sf::Font&  mFont;
			size_t     mNameIndex;
			int        mCharIndex;
			bool       mIsEnabled;
			
			void SetPosition(const sf::Text& nameText);
			void ChangeChar(const CursorUpdate& update);
			char SelectChar(const CursorUpdate& update);
	};

}