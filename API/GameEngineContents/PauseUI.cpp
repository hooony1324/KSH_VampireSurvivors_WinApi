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
}

void PauseUI::Update()
{
}

void PauseUI::Render()
{

}
