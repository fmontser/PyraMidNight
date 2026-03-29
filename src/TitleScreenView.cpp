#include "TitleScreenView.hpp"
#include "Game.hpp"

namespace fknd {
	
	constexpr std::string_view TITLE_STR = "FranKanoid";
	constexpr std::string_view CREDITS_STR = "Insert coin! credits ";
	constexpr std::string_view START_STR = "Press SPACE to start!";
	
	//TODO hardcoded values
	TitleScreenView::TitleScreenView() : ScreenView() {
		//TODO filesystem exception control
		mFont = std::make_shared<sf::Font>("assets/ClearSans-Regular.ttf");
	
		mTitleTxt = std::make_shared<sf::Text>(*mFont);
		mTitleTxt->setString(std::string(TITLE_STR));
		mTitleTxt->setCharacterSize(90);
		mTitleTxt->setFillColor(sf::Color::Blue);
		mTitleTxt->setPosition({100.f, 100.f});
		mTitleTxt->setOutlineColor(sf::Color::Yellow);
		mTitleTxt->setOutlineThickness(4);
	
		mCreditsTxt = std::make_shared<sf::Text>(*mFont);
		mCreditsTxt->setString(std::string(CREDITS_STR).append("0"));
		mCreditsTxt->setCharacterSize(48);
		mCreditsTxt->setFillColor(sf::Color::Blue);
		mCreditsTxt->setPosition({100.f, 500.f});
		mCreditsTxt->setOutlineColor(sf::Color::Yellow);
		mCreditsTxt->setOutlineThickness(3);
	
		mStartTxt = std::make_shared<sf::Text>(*mFont);
		mStartTxt->setScale({0,0}); //TODO Invisible workarround
		mStartTxt->setString(std::string(START_STR));
		mStartTxt->setCharacterSize(40);
		mStartTxt->setFillColor(sf::Color::Blue);
		mStartTxt->setPosition({130.f, 600.f});
		mStartTxt->setOutlineColor(sf::Color::Yellow);
		mStartTxt->setOutlineThickness(3);
	
		mBackgroundTex = std::make_shared<sf::Texture>(sf::Texture("assets/Background.png"));
		mBackground = std::make_shared<sf::Sprite>(sf::Sprite(*mBackgroundTex));
	
		mDrawables.push_back(mBackground);
		mDrawables.push_back(mTitleTxt);
		mDrawables.push_back(mCreditsTxt);
		mDrawables.push_back(mStartTxt);
	}
	
	bool TitleScreenView::Update(Game& game) {
		auto& frameInput = game.GetInputManager().FetchInput();
		auto& deltaTime = game.GetRenderManager().GetDeltaTime();
		auto& window = game.GetRenderManager().GetWindow();
	
		if (frameInput.close)
			window.close();
		if (frameInput.coin) {
			game.AddCredit();
			UpdateCredits(game);
			if (game.GetCredits() > 0)
				mStartTxt->setScale({1,1});
			mCreditsTxt->setString(mCreditsStr);
		}
		if (frameInput.action && game.GetCredits() > 0)
			return false;
		return true;
	}
	
	void TitleScreenView::UpdateCredits(Game& game) {
		mCreditsStr = std::string(CREDITS_STR).append(
			std::to_string(static_cast<int>(game.GetCredits())));
	}
	
}