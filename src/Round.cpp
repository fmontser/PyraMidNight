#include "Round.hpp"
#include "RoundScreenView.hpp"

Round::Round(RoundScreenView& screenView) : 
	mScreenView(screenView) {
	auto& drawables = mScreenView.GetDrawables();
	
	mPlayArea = std::make_shared<sf::RectangleShape>(sf::RectangleShape({576.0f, 864.0f}));
	mPlayArea->setPosition({32,32});
	//TODO delete, only for debug
	mPlayArea->setFillColor(sf::Color({}));
	drawables.push_back(mPlayArea);

	mDeathArea = std::make_shared<sf::RectangleShape>(sf::RectangleShape({576.0f, 64.0f}));
	mDeathArea->setPosition({32, 832});
	//TODO delete, only for debug
	mDeathArea->setFillColor(sf::Color({}));
	drawables.push_back(mDeathArea);

	mBumperTex = std::make_shared<sf::Texture>("assets/Bumper.png");
	mBumper = std::make_shared<Bumper>(*mBumperTex);
	mBumper->setPosition({256, 832});
	drawables.push_back(mBumper);

	mBallTex = std::make_shared<sf::Texture>("assets/Ball.png");
	mBall = std::make_shared<Bumper>(*mBallTex);
	mBall->setScale({0.5f, 0.5f});
	//TODO temp test position
	mBall->setPosition({256, 256});
	drawables.push_back(mBall);
}

//TODO use weak??
Bumper& Round::GetBumper() { return *mBumper;}
