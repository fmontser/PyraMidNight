#include <cmath>
#include <algorithm>
#include "RoundScreenView.hpp"
#include "Game.hpp"
#include "Levels.hpp"

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

	mBumperTex = std::make_shared<sf::Texture>("assets/Bumper.png");
	mBumper = std::make_shared<Bumper>(*mBumperTex);
	mBumper->setPosition({256, 832});
	
	mBallTex = std::make_shared<sf::Texture>("assets/Ball.png");
	mBall = std::make_shared<Ball>(*mBallTex);

	mBlockTex = std::make_shared<sf::Texture>("assets/Block32.png");

	//TODO convert to simple rect
	mDeathArea = std::make_shared<sf::RectangleShape>(sf::RectangleShape({576.0f, 64.0f}));
	mDeathArea->setPosition({32, 864});
	mDeathArea->setFillColor({0,0,0,0});

	mDrawables.push_back(mBackground);
	mDrawables.push_back(mCreditsTxt);
	mDrawables.push_back(mScoreTxt);
	mDrawables.push_back(mWallLeft);
	mDrawables.push_back(mWallRight);
	mDrawables.push_back(mCeil);
	mDrawables.push_back(mBumper);
	mDrawables.push_back(mBall);
	mDrawables.push_back(mDeathArea); //TODO remove on rect convert

	mColdetVector.push_back(mCeil);
	mColdetVector.push_back(mWallLeft);
	mColdetVector.push_back(mWallRight);
	mColdetVector.push_back(mBumper);

	//TODO make it dynamic
	LoadLevel(level1);
}

void RoundScreenView::Update(Game& game) {
	auto& frameInput = game.GetInputManager().FetchInput();
	auto& deltaTime = game.GetRenderManager().GetDeltaTime();
	auto& window = game.GetRenderManager().GetWindow();

	if (frameInput.close)
		window.close();
	if (frameInput.coin)
		game.AddCredit();
 	if (frameInput.action) {
		if (mBall->GetState() == Ball::State::DOCKED)
			mBall->Launch();
	}
	if (frameInput.left)
		mBumper->Move(-1, deltaTime);
	else if (frameInput.right)
		mBumper->Move(1, deltaTime);

	UpdateBall(deltaTime);
	UpdateBlocks();
	UpdateGame(game);
	UpdateCredits(game);
	UpdateScore(game);
}

void RoundScreenView::LoadLevel(const std::array<const std::string, 9>& level) {
	const auto offset =sf::Vector2f(64,32);
	auto actualPos = sf::Vector2f(32,32);

	for (const auto& str : level) {
		for (const auto chara : str) {
			if (chara != '0') {
				auto block = std::make_shared<Block>(*mBlockTex, 1);
				block->setPosition(actualPos);
				mBlockVector.push_back(block);
			}
			actualPos.x += offset.x;
		}
		actualPos.x = 32;
		actualPos.y += offset.y;
	}

	for (const auto& block : mBlockVector) {
		mDrawables.push_back(block);
		mColdetVector.push_back(block);
	}
}

void RoundScreenView::UpdateBall(const sf::Time &deltaTime)
{
	if (mBall->GetState() == Ball::State::PLAYING) {
		for (const auto &obj : mColdetVector) {
			float distance = GetBallDistance(*obj);

			if (distance <= mBall->GetRadius()) {
				mBall->Bounce(*obj, distance);
				if (typeid(*obj) == typeid(Block)) {
					if (dynamic_cast<Block*>(obj.get())->Damage())
						mDestroyedSprites.push_back(obj);
				}
				break;
			}
		}
	}
	mBall->Update(mBumper->getPosition(), deltaTime);
}

void RoundScreenView::UpdateBlocks() {
	for (const auto& sprt : mDestroyedSprites) {
		auto itBlock = std::find(mBlockVector.begin(), mBlockVector.end(), sprt);
		if (itBlock != mBlockVector.end())
			mBlockVector.erase(itBlock);

		auto itColdet = std::find(mColdetVector.begin(), mColdetVector.end(), sprt);
		if (itColdet != mColdetVector.end())
			mColdetVector.erase(itColdet);

		auto itDrawable = std::find(mDrawables.begin(), mDrawables.end(), sprt);
		if (itDrawable != mDrawables.end())
			mDrawables.erase(itDrawable);
	}
	mDestroyedSprites.clear();
}

void RoundScreenView::UpdateGame(Game &game){
	//Lose
	if (mDeathArea->getGlobalBounds().contains(mBall->getPosition()))
		LoseBall(game);
	//Win
	if (mBlockVector.empty())
		game.SetNextRound();
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

void RoundScreenView::LoseBall(Game& game) {
	game.ConsumeCredit();
	//TODO remove score penalty?
	if (game.GetCredits() == 0){
		game.GameOver();
		return;
	}
	//TODO animation?
	mBall->ResetPos(mBumper->getPosition());
};

float RoundScreenView::GetBallDistance(const sf::Sprite& obj) {
	auto bPos = mBall->getPosition();
	auto rect = obj.getGlobalBounds();
	float closestX = std::clamp(bPos.x, rect.position.x, rect.position.x + rect.size.x);
	float closestY = std::clamp(bPos.y, rect.position.y, rect.position.y + rect.size.y);
	float distX = bPos.x - closestX;
	float distY = bPos.y - closestY;
	return std::sqrtf((distX * distX) + (distY * distY));
}
