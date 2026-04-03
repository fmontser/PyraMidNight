#pragma once
#include <string>
#include "ScreenView.hpp"
#include "Common.hpp"

namespace fknd {
	
	class TitleScreenView : public ScreenView {
		public:
			struct TitleScreenUpdate {
				bool     action;
				bool     coin;
				uint8_t& credits;
			};

			TitleScreenView();

			bool Update(const TitleScreenUpdate& update);
	
		private:
			std::shared_ptr<sf::Font> mFont;
			std::shared_ptr<sf::Text> mTitleTxt;
			std::shared_ptr<sf::Text> mCreditsTxt;
			std::shared_ptr<sf::Text> mStartTxt;
			std::shared_ptr<sf::Texture> mBackgroundTex;
			std::shared_ptr<sf::Sprite> mBackground;
	
			std::string mCreditsStr;
	
			void UpdateCredits(uint8_t& credits);
			void ShowStartText();
			void BlinkStartText();
			bool Update();
	};

}