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
			void SetEntry(std::shared_ptr<sf::Text>& entry);
			bool Accept(std::string* gameEntryName);
	
		private:
			std::shared_ptr<sf::Text> mEntryTxt;
			sf::Font& mFont;
			size_t mEntryIndex;
			
			void ChangeChar(Input action);
			char SelectChar(Input action);
	};

}