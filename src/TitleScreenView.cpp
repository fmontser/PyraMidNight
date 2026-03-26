#include "TitleScreenView.hpp"
#include "Game.hpp"

//TODO hardcoded values
TitleScreenView::TitleScreenView() : ScreenView() {
	backgroundTex = std::make_shared<sf::Texture>(sf::Texture("assets/Background.png"));
	background = std::make_shared<sf::Sprite>(sf::Sprite(*backgroundTex));
	mDrawables.push_back(background);
}

void TitleScreenView::ProcessInput(Game& game) {
	auto& frameInput = game.GetInputManager().FetchInput();
	auto& deltaTime = game.GetRenderManager().GetDeltaTime();
	auto& window = game.GetRenderManager().GetWindow();

	if (frameInput.close)
			window.close();
	if (frameInput.coin)
			game.AddCredit();
}