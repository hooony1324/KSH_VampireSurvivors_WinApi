#include "PauseUI.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngine/GameEngineRenderer.h>


PauseUI::PauseUI() 
{
}

PauseUI::~PauseUI() 
{
}

void PauseUI::Start()
{
	SetScale(GameEngineWindow::GetScale());
	SetPosition(float4::ZERO);

	GameEngineRenderer* Renderer_ = CreateRenderer("BlackBG.bmp");
	Renderer_->SetAlpha(100);
	Renderer_->SetPivot(GameEngineWindow::GetScale().Half());
	Renderer_->CameraEffectOff();

	float4 Scale = GameEngineWindow::GetScale();

	GameEngineRenderer* OptionButton_ = CreateRenderer("OptionButton.bmp");
	OptionButton_->CameraEffectOff();
	OptionButton_->SetScale(OptionButton_->GetScale());
	OptionButton_->SetPivot({ Scale.Half().x - 144, Scale.y - 65});

	GameEngineRenderer* ContinueButton_ = CreateRenderer("ContinueButton.bmp");
	ContinueButton_->CameraEffectOff();
	ContinueButton_->SetScale(ContinueButton_->GetScale());
	ContinueButton_->SetPivot({ Scale.Half().x + 144, Scale.y - 65});
}

void PauseUI::Update()
{
}

void PauseUI::Render()
{

}
