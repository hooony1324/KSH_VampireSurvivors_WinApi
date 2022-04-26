#include "Arrow.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>

Arrow::Arrow() 
{
}

Arrow::~Arrow() 
{
}

void Arrow::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale({ 100, 100 });

	TargetRenderer_ = nullptr;

	ArrowL_ = CreateRenderer();
	ArrowL_->CreateAnimation("Arrow_R.bmp", "ArrowR", 0, 7, 0.1f, true);
	ArrowL_->ChangeAnimation("ArrowR");
	ArrowL_->Off();

	ArrowR_ = CreateRenderer();
	ArrowR_->CreateAnimation("Arrow_L.bmp", "ArrowL", 0, 7, 0.1f, true);
	ArrowR_->ChangeAnimation("ArrowL");
	ArrowR_->Off();

	NextLevelOff();
}

void Arrow::Update()
{
	// 애로우 표시, Buttons일때만
	if (nullptr != TargetRenderer_)
	{
		ArrowL_->On();
		ArrowR_->On();

		ArrowL_->SetPivot(TargetRenderer_->GetPivot() + float4{ -TargetRenderer_->GetScale().Half().x - 20, 0 });
		ArrowR_->SetPivot(TargetRenderer_->GetPivot() + float4{ TargetRenderer_->GetScale().Half().x + 20, 0 });

	}
	else
	{
		ArrowL_->Off();
		ArrowR_->Off();
	}
}

void Arrow::Render()
{

}
