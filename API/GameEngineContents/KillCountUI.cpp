#include "KillCountUI.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>

#include "GameInfo.h"

KillCountUI::KillCountUI() 
{
}

KillCountUI::~KillCountUI() 
{
}

void KillCountUI::Start()
{
	SetPosition(float4{GameEngineWindow::GetScale().Half().x, 0 } + float4{410, 45});
	SetScale(float4{60, 30});

	GameEngineRenderer* Renderer_ = CreateRenderer("SkullToken.bmp");
	Renderer_->CameraEffectOff();

	TextFont_.Load("../Resources/UI/KO.ttf");

	NextLevelOff();
}

void KillCountUI::Update()
{
}

void KillCountUI::Render()
{
	std::string KillCount = std::to_string(GameInfo::GetPlayerInfo()->KillCount_);
	int StrLength = static_cast<int>(KillCount.length()) - 1;
	int Space = 8 * StrLength;

	TextFont_.Draw(KillCount, { GetPosition().x - 22 - Space, GetPosition().y - 11}, 23, 800);
}
