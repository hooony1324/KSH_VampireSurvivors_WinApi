#include "TitleBackGround.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>

TitleBackGround::TitleBackGround() 
{
}

TitleBackGround::~TitleBackGround() 
{
}

void TitleBackGround::Start()
{
	SetPosition(float4::ZERO);
	SetScale(GameEngineWindow::GetScale());

	GameEngineRenderer* Renderer = CreateRenderer("MainBG.bmp");
	Renderer->SetPivot(GameEngineWindow::GetScale().Half());
}

void TitleBackGround::Render()
{

}

