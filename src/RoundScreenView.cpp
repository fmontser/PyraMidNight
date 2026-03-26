#include "RoundScreenView.hpp"
#include "Game.hpp"

//TODO remove 
constexpr std::string_view CREDITS_STR = "CREDITS ";
constexpr std::string_view SCORE_STR = "SCORE ";

//TODO hardcoded values
RoundScreenView::RoundScreenView() : ScreenView() {
	//TODO filesystem exception control
	mFont = std::make_shared<sf::Font>("assets/ClearSans-Regular.ttf");

	mCreditsTxt = std::make_shared<sf::Text>(*mFont);
	mCreditsTxt->setString(std::string(CREDITS_STR));
	mCreditsTxt->setCharacterSize(24);
	mCreditsTxt->setFillColor(sf::Color::White);
	mCreditsTxt->setPosition({128.f, 864.f});
	mCreditsTxt->setOutlineColor(sf::Color::Blue);
	mCreditsTxt->setOutlineThickness(1);

	mScoreTxt = std::make_shared<sf::Text>(*mFont);
	mScoreTxt->setString(std::string(SCORE_STR));
	mScoreTxt->setCharacterSize(24);
	mScoreTxt->setFillColor(sf::Color::White);
	mScoreTxt->setPosition({352.f, 864.f});
	mScoreTxt->setOutlineColor(sf::Color::Blue);
	mScoreTxt->setOutlineThickness(1);
	
	mBackgroundTex = std::make_shared<sf::Texture>(sf::Texture("assets/Background.png"));
	mBackground = std::make_shared<sf::Sprite>(sf::Sprite(*mBackgroundTex));
	mBackground->setColor(sf::Color({0, 0, 255, 128})); //TODO tint
	
	mWallTex = std::make_shared<sf::Texture>(sf::Texture("assets/Wall32.png"));
	mWallTex->setRepeated(true);
	mWallLeft = std::make_shared<sf::Sprite>(sf::Sprite(*mWallTex));
	mWallLeft->setTextureRect({{0, 0},{32, 896}});
	mWallLeft->setPosition({0, 32});
	mWallRight = std::make_shared<sf::Sprite>(sf::Sprite(*mWallTex));
	mWallRight->setTextureRect({{0, 0},{32, 896}});
	mWallRight->setPosition({608, 32});

	mCeilTex = std::make_shared<sf::Texture>(sf::Texture("assets/Ceil32.png"));
	mCeilTex->setRepeated(true);
	mCeil = std::make_shared<sf::Sprite>(*mCeilTex);
	mCeil->setTextureRect({{0, 0},{640, 32}});

	mDrawables.push_back(mBackground);
	mDrawables.push_back(mCreditsTxt);
	mDrawables.push_back(mScoreTxt);
	mDrawables.push_back(mWallLeft);
	mDrawables.push_back(mWallRight);
	mDrawables.push_back(mCeil);

	mRound = std::make_unique<Round>(*this);
}

void RoundScreenView::ProcessInput(Game& game) {
	auto& frameInput = game.GetInputManager().FetchInput();
	auto& deltaTime = game.GetRenderManager().GetDeltaTime();
	auto& window = game.GetRenderManager().GetWindow();

	if (frameInput.close)
		window.close();
	if (frameInput.coin)
		game.AddCredit();
	if (frameInput.action && game.GetCredits() > 0)
		game.SetState(Game::State::ROUND_SCREEN);

	UpdateCredits(game);
	UpdateScore(game);
}

void RoundScreenView::UpdateCredits(Game& game) {
	mCreditsTxt->setString(std::string(CREDITS_STR)
		.append(std::to_string(static_cast<int>(game.GetCredits()))));
}

void RoundScreenView::UpdateScore(Game& game) {
	//TODO delete score test
	game.AddScore(1);

	mScoreTxt->setString(std::string(SCORE_STR)
		.append(std::to_string(static_cast<int>(game.GetScore()))));
}