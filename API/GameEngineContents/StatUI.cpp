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
	GameEngineRenderer* RendererBack = CreateRenderer("StatUI.bmp");
	GameEngineRenderer* RendererText = CreateRenderer("StatUIText.bmp");


	SetScale(RendererBack->GetScale());
	RendererBack->SetAlpha(100);
	RendererBack->CameraEffectOff();
	RendererBack->SetPivot(RendererBack->GetScale().Half());

	RendererText->CameraEffectOff();
	RendererText->SetPivot(RendererText->GetScale().Half());



}

void StatUI::Update()
{
}

void StatUI::Render()
{
}
