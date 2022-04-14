#include "LevelUpUI.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineSound.h>

#include "ObjectEnum.h"
#include "GameInfo.h"

int LevelUpUI::CreateCount_ = 0;
bool LevelUpUI::IsActivated_ = false;

LevelUpUI::LevelUpUI() 
{
}

LevelUpUI::~LevelUpUI() 
{
}

void LevelUpUI::Start()
{

	GameEngineRenderer* Renderer = CreateRenderer("LevelUpUI.bmp");
	SetScale(Renderer->GetScale());
	Renderer->CameraEffectOff();
	Renderer->SetPivot(GameEngineWindow::GetScale().Half());

	GameEngineSound::SoundPlayOneShot("LevelUp.MP3", 0);
	GameInfo::SetPause(true);
	IsActivated_ = true;
}

void LevelUpUI::Update()
{
	if (0 >= CreateCount_)
	{
		return;
	}


	// 아이템 선택
	if (true == GameEngineInput::GetInst()->IsDown("Num1"))
	{
		



		// 종료
		Death();
		CreateCount_--;
		GameInfo::SetPause(false);
		IsActivated_ = false;
	}


}

void LevelUpUI::Render()
{
}
