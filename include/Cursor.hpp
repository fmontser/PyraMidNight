#pragma once
#include <SFML/Graphics.hpp>

//TODO text cursor for records!
class Cursor : public sf::RectangleShape {
	public:
		enum class Action {
			LEFT, RIGHT, UP, DOWN
		};

		Cursor(sf::Font& font);

		void Control(Action action);
		void SetEntry(std::shared_ptr<sf::Text>& entry);
		bool Accept(std::string* gameEntryName);

	private:
		std::shared_ptr<sf::Text> mEntryTxt;
		sf::Font& mFont;
		size_t mEntryIndex;
		
		void ChangeChar(Action action);
		char SelectChar(Action action);

		

};