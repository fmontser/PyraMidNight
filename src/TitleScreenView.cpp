#include "TitleScreenView.hpp"
#include "Game.hpp"

constexpr std::string_view CREDITS_STR = "Insert coin! credits ";
constexpr std::string_view START_STR = "Press SPACE to start!";

//TODO hardcoded values
TitleScreenView::TitleScreenView() : ScreenView() {
	//TODO filesystem exception control
	font = std::make_shared<sf::Font>("assets/ClearSans-Regular.ttf");

	titleTxt = std::make_shared<sf::Text>(*font);
	titleTxt->setString("FranKanoid");
	titleTxt->setCharacterSize(90);
	titleTxt->setFillColor(sf::Color::Blue);
	titleTxt->setPosition({100.f, 100.f});
	titleTxt->setOutlineColor(sf::Color::Yellow);
	titleTxt->setOutlineThickness(4);

	creditsTxt = std::make_shared<sf::Text>(*font);
	creditsTxt->setString(std::string(CREDITS_STR).append("0"));
	creditsTxt->setCharacterSize(48);
	creditsTxt->setFillColor(sf::Color::Blue);
	creditsTxt->setPosition({100.f, 500.f});
	creditsTxt->setOutlineColor(sf::Color::Yellow);
	creditsTxt->setOutlineThickness(3);

	startTxt = std::make_shared<sf::Text>(*font);
	startTxt->setScale({0,0}); //TODO Invisible workarround
	startTxt->setString(std::string(START_STR));
	startTxt->setCharacterSize(40);
	startTxt->setFillColor(sf::Color::Blue);
	startTxt->setPosition({130.f, 600.f});
	startTxt->setOutlineColor(sf::Color::Yellow);
	startTxt->setOutlineThickness(3);

	mBackgroundTex = std::make_shared<sf::Texture>(sf::Texture("assets/Background.png"));
	mBackground = std::make_shared<sf::Sprite>(sf::Sprite(*mBackgroundTex));

	mDrawables.push_back(mBackground);
	mDrawables.push_back(titleTxt);
	mDrawables.push_back(creditsTxt);
	mDrawables.push_back(startTxt);
}

void TitleScreenView::Update(Game& game) {
	auto& frameInput = game.GetInputManager().FetchInput();
	auto& deltaTime = game.GetRenderManager().GetDeltaTime();
	auto& window = game.GetRenderManager().GetWindow();

	if (frameInput.close)
		window.close();
	if (frameInput.coin) {
		game.AddCredit();
		UpdateCredits(game);
		if (game.GetCredits() > 0)
			startTxt->setScale({1,1});
		creditsTxt->setString(creditsStr);
	}
	if (frameInput.action && game.GetCredits() > 0)
		game.SetState(Game::State::ROUND_SCREEN);
}

void TitleScreenView::UpdateCredits(Game& game) {
	creditsStr = std::string(CREDITS_STR).append(
		std::to_string(static_cast<int>(game.GetCredits())));
}