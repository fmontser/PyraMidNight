#pragma once
#include <string>
#include "ScreenView.hpp"
#include "Cursor.hpp"
#include "Common.hpp"

namespace fknd {
	
	class MenuScreenView : public ScreenView {
		public:
			struct MenuScreenUpdate {
				//TODO
				bool action;
				bool menu;
			};
			
			MenuScreenView();

			bool Update(MenuScreenUpdate update);
			
		private:

			std::shared_ptr<sf::Font>           mFont;
			std::shared_ptr<sf::Text>           mBgmTxt;
			std::shared_ptr<sf::Text>           mSfxTxt;
			std::shared_ptr<sf::Text>           mExitTxt;
			std::shared_ptr<sf::Texture>        mBackgroundTex;
			std::shared_ptr<sf::Sprite>         mBackground;
			std::shared_ptr<Cursor>             mCursor;
	
			bool Update();
	};

}