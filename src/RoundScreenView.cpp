#include "RoundScreenView.hpp"
#include "Game.hpp"

//TODO remove 
constexpr std::string_view STUB_STR = "STUB TEXT FOR ROUND SCREEN";

//TODO hardcoded values
RoundScreenView::RoundScreenView() : ScreenView() {
	//TODO filesystem exception control
	font = std::make_shared<sf::Font>("assets/ClearSans-Regular.ttf");

	stubTxt = std::make_shared<sf::Text>(*font);
	stubTxt->setString(std::string(STUB_STR));
	stubTxt->setCharacterSize(24);
	stubTxt->setFillColor(sf::Color::Blue);
	stubTxt->setPosition({100.f, 100.f});
	stubTxt->setOutlineColor(sf::Color::Yellow);
	stubTxt->setOutlineThickness(4);

	backgroundTex = std::make_shared<sf::Texture>(sf::Texture("assets/Background.png"));
	background = std::make_shared<sf::Sprite>(sf::Sprite(*backgroundTex));
	background->setColor(sf::Color({0,0,255,128})); //TODO tint

	mDrawables.push_back(background);
	mDrawables.push_back(stubTxt);
}

void RoundScreenView::ProcessInput(Game& game) {
	auto& frameInput = game.GetInputManager().FetchInput();
	auto& deltaTime = game.GetRenderManager().GetDeltaTime();
	auto& window = game.GetRenderManager().GetWindow();

	if (frameInput.close)
		window.close();
	if (frameInput.coin) {
		game.AddCredit();
		UpdateCredits(game);
		//TODO credits gui
/* 		if (game.GetCredits() > 0)
			startTxt->setScale({1,1});
		creditsTxt->setString(creditsStr); */
	}
	if (frameInput.action && game.GetCredits() > 0)
		game.SetState(Game::State::ROUND_SCREEN);
}

void RoundScreenView::UpdateCredits(Game& game) {
	//TODO
/* 	creditsStr = std::string(CREDITS_STR).append(
		std::to_string(static_cast<int>(game.GetCredits()))); */
}