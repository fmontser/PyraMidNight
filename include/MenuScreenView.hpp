#pragma once
#include <string>
#include "ScreenView.hpp"
#include "Common.hpp"

namespace fknd {
	
	class MenuScreenView : public ScreenView {
		public:
			enum Option {
				BGM, SFX, EXIT
			};

			struct MenuScreenUpdate {
				//TODO
				bool action;
				bool menu;
				bool left;
				bool right;
				bool up;
				bool down;
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

			uint8_t mBgmVolume;
			uint8_t mSfxVolume;
			Option  option;
			std::vector<std::shared_ptr<sf::Text>> mTexts;

			void UpdateBgmVolume(float volume);
			void UpdateSfxVolume(float volume);
			void SelectOption(bool up, bool down);
			void InvertOptionColors(std::shared_ptr<sf::Text> option);
	
			bool Update();
	};

}