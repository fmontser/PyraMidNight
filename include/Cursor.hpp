#pragma once
#include <SFML/Graphics.hpp>
#include "Common.hpp"

namespace fknd {
	
	class Cursor : public sf::RectangleShape {
		public:
			enum class Input {
				LEFT, RIGHT, UP, DOWN, ACTION
			};
	
			Cursor(sf::Font& font);
	
			void Update(Input action);
			void SetEntry(sf::Text* entry);
			bool Accept(std::string* gameEntryName);
			void Blink();
	
		private:
			sf::Text* mEntryTxt;
			sf::Font& mFont;
			size_t    mEntryIndex;
			sf::Clock mClock;
			
			void ChangeChar(Input action);
			char SelectChar(Input action);
	};

}