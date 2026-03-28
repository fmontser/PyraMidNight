#include "EndScreenView.hpp"
#include "Game.hpp"

constexpr std::string_view TITLE_STR = "GAME OVER!";
constexpr std::string_view CREDITS_STR = "Insert coin! credits ";
constexpr std::string_view START_STR = "Press SPACE to start!";

//TODO hardcoded values
EndScreenView::EndScreenView() : ScreenView() {
	//TODO filesystem exception control
	mFont = std::make_shared<sf::Font>("assets/ClearSans-Regular.ttf");

	mTitleTxt = std::make_shared<sf::Text>(*mFont);
	mTitleTxt->setString(std::string(TITLE_STR));
	mTitleTxt->setCharacterSize(80);
	mTitleTxt->setFillColor(sf::Color::Blue);
	mTitleTxt->setPosition({100.f, 100.f});
	mTitleTxt->setOutlineColor(sf::Color::Yellow);
	mTitleTxt->setOutlineThickness(4);

	//TODO make dynamic score ranking
	mCreditsTxt = std::make_shared<sf::Text>(*mFont);
	mCreditsTxt->setString(std::string(CREDITS_STR).append("0"));
	mCreditsTxt->setCharacterSize(48);
	mCreditsTxt->setFillColor(sf::Color::Blue);
	mCreditsTxt->setPosition({100.f, 500.f});
	mCreditsTxt->setOutlineColor(sf::Color::Yellow);
	mCreditsTxt->setOutlineThickness(3);
	//##########


	mStartTxt = std::make_shared<sf::Text>(*mFont);
	mStartTxt->setString(std::string(START_STR));
	mStartTxt->setCharacterSize(40);
	mStartTxt->setFillColor(sf::Color::Blue);
	mStartTxt->setPosition({130.f, 600.f});
	mStartTxt->setOutlineColor(sf::Color::Yellow);
	mStartTxt->setOutlineThickness(3);

	mBackgroundTex = std::make_shared<sf::Texture>(sf::Texture("assets/Background.png"));
	mBackground = std::make_shared<sf::Sprite>(sf::Sprite(*mBackgroundTex));
	mBackground->setColor({64, 0, 0, 255});

	mDrawables.push_back(mBackground);
	mDrawables.push_back(mTitleTxt);
	mDrawables.push_back(mCreditsTxt);
	mDrawables.push_back(mStartTxt);
}

void EndScreenView::Update(Game& game) {
	auto& frameInput = game.GetInputManager().FetchInput();
	auto& deltaTime = game.GetRenderManager().GetDeltaTime();
	auto& window = game.GetRenderManager().GetWindow();

	if (frameInput.close)
		window.close();

	if (frameInput.action)
		game.SetState(Game::State::TITLE_SCREEN);
}