#include "LevelUpBox.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GameEnum.h"
#include "GameInfo.h"
#include "LevelUpUI.h"

LevelUpBox::LevelUpBox() 
	: Col_(nullptr)
{
}

LevelUpBox::~LevelUpBox() 
{
}

void LevelUpBox::Start()
{
	GameEngineRenderer* Renderer_ = CreateRenderer("BoxOpen.bmp");
	SetScale(Renderer_->GetScale());

	Col_ = CreateCollision("LevelUpBox", Renderer_->GetScale());

	NextLevelOff();
}

void LevelUpBox::Update()
{
	if (false == Col_->CollisionCheck("Player"))
	{
		return;
	}


	// 일단은 LevelUPUI, 추후에 보물상자 에니메이션으로
	LevelUpUI::State_ = LevelUpUI::STATE::BOXES;
	LevelUpUI::CreateCount_ += 1;
	
	// LevelUpUI상태설정
	// 8레벨 무기 있으면 패시브의 조합 확인
	// LevelUpUI상태 -> 각성무기
	

	Death();

}

void LevelUpBox::Render()
{
}