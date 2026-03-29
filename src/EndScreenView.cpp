#include <algorithm>
#include "EndScreenView.hpp"
#include "Game.hpp"

constexpr std::string_view TITLE_STR = "GAME OVER!";
constexpr std::string_view CONTINUE_STR = "Press SPACE to continue!";

//TODO hardcoded values
EndScreenView::EndScreenView() : ScreenView() {
	mIsRankingDraw = false;
	mIsNameSet =  false;

	//TODO filesystem exception control
	mFont = std::make_shared<sf::Font>("assets/ClearSans-Regular.ttf");
	mCursor = std::make_shared<Cursor>(*mFont);

	mTitleTxt = std::make_shared<sf::Text>(*mFont);
	mTitleTxt->setString(std::string(TITLE_STR));
	mTitleTxt->setCharacterSize(80);
	mTitleTxt->setFillColor(sf::Color::Blue);
	mTitleTxt->setOutlineColor(sf::Color::Yellow);
	mTitleTxt->setOutlineThickness(4);
	mTitleTxt->setPosition({100.f, 100.f});

	//TODO make dynamic score ranking
	auto rankingEntryPos = sf::Vector2f({100.0f, 160.0f});
	for (size_t i = 0; i < 10; i++) {
		auto nameEntry = std::make_shared<sf::Text>(*mFont);
		nameEntry->setString("AAA");
		auto textOffset = sf::Vector2f({160.0f, 40.0f});

		rankingEntryPos.y += textOffset.y;
		nameEntry->setCharacterSize(48);
		nameEntry->setFillColor(sf::Color::White);
		nameEntry->setOutlineColor(sf::Color::Blue);
		nameEntry->setOutlineThickness(1);
		nameEntry->setPosition(rankingEntryPos);

		auto scoreEntry = std::make_shared<sf::Text>(*mFont);
		scoreEntry->setString("0000000000");

		rankingEntryPos.x += textOffset.x;
		scoreEntry->setCharacterSize(48);
		scoreEntry->setFillColor(sf::Color::White);
		scoreEntry->setOutlineColor(sf::Color::Blue);
		scoreEntry->setOutlineThickness(1);
		scoreEntry->setPosition(rankingEntryPos);
		rankingEntryPos.x -= textOffset.x;

		mRankingTxt.push_back({nameEntry, scoreEntry});
	}
	
	mStartTxt = std::make_shared<sf::Text>(*mFont);
	mStartTxt->setString(std::string(CONTINUE_STR));
	mStartTxt->setCharacterSize(40);
	mStartTxt->setFillColor({0, 0, 0, 0});
	mStartTxt->setOutlineColor({0, 0, 0, 0});
	mStartTxt->setOutlineThickness(3);
	mStartTxt->setPosition({100.f, 650.f});

	mBackgroundTex = std::make_shared<sf::Texture>(sf::Texture("assets/Background.png"));
	mBackground = std::make_shared<sf::Sprite>(sf::Sprite(*mBackgroundTex));
	mBackground->setColor({64, 0, 0, 255});

	mDrawables.push_back(mBackground);
	mDrawables.push_back(mTitleTxt);
	mDrawables.push_back(mStartTxt);

	for (const auto& entry : mRankingTxt) {
		mDrawables.push_back(entry.name);
		mDrawables.push_back(entry.score);
	}

	mDrawables.push_back(mCursor);
}

bool EndScreenView::Update(Game& game) {
	auto& frameInput = game.GetInputManager().FetchInput();
	auto& window = game.GetRenderManager().GetWindow();

	if (!mIsRankingDraw) {
		mIsRankingDraw = SetGameRanking(game);
			
		//Find record for cursor
		for (auto& text : mRankingTxt) {
			if (text.name->getString() == "???")
				mCursor->SetEntry(text.name);
		}
	}
	if (frameInput.close)
		window.close();
	if (!mIsNameSet) {
		if (frameInput.left)
		mCursor->Control(Cursor::Action::LEFT);
		else if (frameInput.right)
		mCursor->Control(Cursor::Action::RIGHT);
		else if (frameInput.up)
		mCursor->Control(Cursor::Action::UP);
		else if (frameInput.down)
		mCursor->Control(Cursor::Action::DOWN);
		else if (frameInput.action) {
			mIsNameSet = mCursor->Accept(GetGameEntryName(game));
			mStartTxt->setFillColor(sf::Color::Blue);
			mStartTxt->setOutlineColor(sf::Color::Yellow);
			return true;
		}
	}
	if (frameInput.action && mIsNameSet)
		return false;
	return true;
}

bool EndScreenView::SetGameRanking(Game& game) {
	auto ranking = game.GetRanking();
	size_t i = 0;

	for (auto& gameEntry : ranking) {
		if (i < mRankingTxt.size()) {
			mRankingTxt[i].name->setString(gameEntry.name);
			mRankingTxt[i].score->setString(PadZeroScore(gameEntry.score, 10));
		}
		i++;
	}
	return true;
}

std::string* EndScreenView::GetGameEntryName(Game &game) {
	for (auto& gameEntry : game.GetRanking()) {
		if (gameEntry.name == "???")
			return &gameEntry.name;
	}
}

std::string EndScreenView::PadZeroScore(uint32_t score, uint32_t digits) {
	std::ostringstream ss;

	ss << std::setw(digits) << std::setfill('0') << score;
	return ss.str();
}
