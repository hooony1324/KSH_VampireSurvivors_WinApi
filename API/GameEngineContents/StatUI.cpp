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
	SetPosition({10, 100});

	GameEngineRenderer* Renderer_ = CreateRenderer("StatUI.bmp");
	Renderer_->CameraEffectOff();

	float4 scale = Renderer_->GetScale();
	SetScale(Renderer_->GetScale());
}

void StatUI::Update()
{
}

void StatUI::Render()
{
}
