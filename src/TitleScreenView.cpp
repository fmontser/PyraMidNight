#include "TitleScreenView.hpp"
#include "Game.hpp"

constexpr std::string_view CREDITS_STR = "Insert coin! credits ";

//TODO hardcoded values
TitleScreenView::TitleScreenView() : ScreenView() {
	//TODO filesystem exception control
	creditsStr = "Insert coin! credits 0";
	font = std::make_shared<sf::Font>("assets/ClearSans-Regular.ttf");

	titleTxt = std::make_shared<sf::Text>(*font);
	titleTxt->setString("FranKanoid");
	titleTxt->setCharacterSize(90);
	titleTxt->setFillColor(sf::Color::Blue);
	titleTxt->setPosition({100.f, 100.f});
	titleTxt->setOutlineColor(sf::Color::Yellow);
	titleTxt->setOutlineThickness(4);

	creditsTxt = std::make_shared<sf::Text>(*font);
	creditsTxt->setString(creditsStr);
	creditsTxt->setCharacterSize(48);
	creditsTxt->setFillColor(sf::Color::Blue);
	creditsTxt->setPosition({100.f, 500.f});
	creditsTxt->setOutlineColor(sf::Color::Yellow);
	creditsTxt->setOutlineThickness(3);

	backgroundTex = std::make_shared<sf::Texture>(sf::Texture("assets/Background.png"));
	background = std::make_shared<sf::Sprite>(sf::Sprite(*backgroundTex));

	mDrawables.push_back(background);
	mDrawables.push_back(titleTxt);
	mDrawables.push_back(creditsTxt);
}

void TitleScreenView::ProcessInput(Game& game) {
	auto& frameInput = game.GetInputManager().FetchInput();
	auto& deltaTime = game.GetRenderManager().GetDeltaTime();
	auto& window = game.GetRenderManager().GetWindow();

	if (frameInput.close)
		window.close();
	if (frameInput.coin) {
		game.AddCredit();
		creditsStr = std::string(CREDITS_STR).append(
			std::to_string(static_cast<int>(game.GetCredits())));
		creditsTxt->setString(creditsStr);
	}
}