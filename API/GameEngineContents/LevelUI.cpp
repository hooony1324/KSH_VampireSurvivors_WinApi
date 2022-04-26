#include "LevelUI.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
//#include <GameEngineBase/GameEngineDebug.h>

#include "GameEnum.h"
#include <GameEngine/GameEngineRenderer.h>
#include "GameInfo.h"
#include <string>


#include "Vector2D.h"


LevelUI::LevelUI()
	: BackBufferDC_(nullptr)
	, PlayerLevel_(0)
{
}

LevelUI::~LevelUI() 
{
}

void LevelUI::Start()
{
	SetPosition({ GameEngineWindow::GetScale().x - 50, 0 });
	SetScale({ 100, 30 });

	// 폰트 설정
	/*SetTextColor(GameEngine::BackBufferDC(), RGB(255, 255, 255));
	SetBkMode(GameEngine::BackBufferDC(), TRANSPARENT);*/


	TextFont_.Load("../Resources/PlayUI/KO.ttf");

	NextLevelOff();
}

void LevelUI::Update()
{
	PlayerLevel_ = GameInfo::GetPlayerInfo()->Level_;
}

void LevelUI::Render()
{
	std::string Level = std::to_string(PlayerLevel_);
	int StrLength = static_cast<int>(Level.length()) - 1;
	int Space = 12 * StrLength;

	TextFont_.Draw("LV" + Level, { GameEngineWindow::GetScale().x - 45 - Space, 4.0f}, 23, 800);
}
