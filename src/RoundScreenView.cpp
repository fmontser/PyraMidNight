#include "RoundScreenView.hpp"
#include "Game.hpp"

//TODO remove 
constexpr std::string_view CREDITS_STR = "CREDITS ";
constexpr std::string_view SCORE_STR = "SCORE ";

//TODO hardcoded values
RoundScreenView::RoundScreenView() : ScreenView() {
	//TODO filesystem exception control
	font = std::make_shared<sf::Font>("assets/ClearSans-Regular.ttf");

	creditsTxt = std::make_shared<sf::Text>(*font);
	creditsTxt->setString(std::string(CREDITS_STR));
	creditsTxt->setCharacterSize(24);
	creditsTxt->setFillColor(sf::Color::White);
	creditsTxt->setPosition({128.f, 864.f});
	creditsTxt->setOutlineColor(sf::Color::Blue);
	creditsTxt->setOutlineThickness(1);

	scoreTxt = std::make_shared<sf::Text>(*font);
	scoreTxt->setString(std::string(SCORE_STR));
	scoreTxt->setCharacterSize(24);
	scoreTxt->setFillColor(sf::Color::White);
	scoreTxt->setPosition({352.f, 864.f});
	scoreTxt->setOutlineColor(sf::Color::Blue);
	scoreTxt->setOutlineThickness(1);
	
	backgroundTex = std::make_shared<sf::Texture>(sf::Texture("assets/Background.png"));
	background = std::make_shared<sf::Sprite>(sf::Sprite(*backgroundTex));
	background->setColor(sf::Color({0, 0, 255, 128})); //TODO tint
	
	wallTex = std::make_shared<sf::Texture>(sf::Texture("assets/Wall32.png"));
	wallTex->setRepeated(true);
	wallLeft = std::make_shared<sf::Sprite>(sf::Sprite(*wallTex));
	wallLeft->setTextureRect({{0, 0},{32, 896}});
	wallLeft->setPosition({0, 32});
	wallRight = std::make_shared<sf::Sprite>(sf::Sprite(*wallTex));
	wallRight->setTextureRect({{0, 0},{32, 896}});
	wallRight->setPosition({608, 32});

	ceilTex = std::make_shared<sf::Texture>(sf::Texture("assets/Ceil32.png"));
	ceilTex->setRepeated(true);
	ceil = std::make_shared<sf::Sprite>(*ceilTex);
	ceil->setTextureRect({{0, 0},{640, 32}});

	mDrawables.push_back(background);
	mDrawables.push_back(creditsTxt);
	mDrawables.push_back(scoreTxt);
	mDrawables.push_back(wallLeft);
	mDrawables.push_back(wallRight);
	mDrawables.push_back(ceil);

	round = std::make_unique<Round>(*this);
}

void RoundScreenView::ProcessInput(Game& game) {
	auto& frameInput = game.GetInputManager().FetchInput();
	auto& deltaTime = game.GetRenderManager().GetDeltaTime();
	auto& window = game.GetRenderManager().GetWindow();

	if (frameInput.close)
		window.close();
	if (frameInput.coin) {
		game.AddCredit();
	}
	if (frameInput.action && game.GetCredits() > 0)
		game.SetState(Game::State::ROUND_SCREEN);

	UpdateCredits(game);
	UpdateScore(game);
}

void RoundScreenView::UpdateCredits(Game& game) {
	creditsTxt->setString(std::string(CREDITS_STR)
		.append(std::to_string(static_cast<int>(game.GetCredits()))));
}

void RoundScreenView::UpdateScore(Game& game) {
	//TODO delete score test
	game.AddScore(1);

	scoreTxt->setString(std::string(SCORE_STR)
		.append(std::to_string(static_cast<int>(game.GetScore()))));
}