#include "ExpBar.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
//#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngine/GameEngineRenderer.h>

#include "GameInfo.h"

ExpBar::ExpBar() 
{
}

ExpBar::~ExpBar() 
{
}

void ExpBar::Start()
{
	SetPosition({GameEngineWindow::GetScale().Half().x, 15});
	SetScale({ 1280, 30 });

	BlackBar_ = CreateRenderer("ExpBar.bmp");
	//BlackBar->SetPivot(BlackBar->GetScale().Half());
	BlackBar_->CameraEffectOff();

	BlueBar_ = CreateRenderer("ExpBarBlue.bmp");
	//BlueBar->SetPivot(BlueBar->GetScale().Half());
	BlueBar_->CameraEffectOff();
}

void ExpBar::Update()
{
	ExpBarUpdate();
}

void ExpBar::Render()
{
	
}

void ExpBar::ExpBarUpdate()
{
	
	float MaxExp = GameInfo::GetPlayerInfo()->MaxExp_;
	float CurrentExp = GameInfo::GetPlayerInfo()->CurrentExp_;
	float BlueRatio = CurrentExp / MaxExp;

	if (BlueRatio > 0)
	{
		BlueBar_->On();
	}
	else
	{
		BlueBar_->Off();
	}


	float BlueBarSizeX = BlackBar_->GetScale().x * BlueRatio;
	BlueBar_->SetScale(float4{ BlueBarSizeX, BlueBar_->GetScale().y });

	float BlackBarSizeX = BlackBar_->GetScale().x;
	float BlueBarPivotX = ((BlackBarSizeX - BlueBarSizeX) / 2);
	BlueBar_->SetPivot(float4{ -BlueBarPivotX, 0 });

}
