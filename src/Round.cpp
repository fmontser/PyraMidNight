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
	mBumper->setTextureRect({{0, 0},{128, 32}});
	mBumper->setPosition({256, 832});
	drawables.push_back(mBumper);
}

//TODO use weak??
Bumper& Round::GetBumper() { return *mBumper;}
