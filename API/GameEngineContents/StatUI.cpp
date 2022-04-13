#include "StatUI.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
//#include <GameEngineBase/GameEngineDebug.h>

#include <GameEngine/GameEngineRenderer.h>

StatUI::StatUI() 
{
}

StatUI::~StatUI() 
{
}

void StatUI::Start()
{
	SetPosition(float4{8, 40});
	GameEngineRenderer* Renderer_ = CreateRenderer("StatUI.bmp");
	SetScale(Renderer_->GetScale());
	Renderer_->CameraEffectOff();
	Renderer_->SetPivot(Renderer_->GetScale().Half());



}

void StatUI::Update()
{
}

void StatUI::Render()
{
}
