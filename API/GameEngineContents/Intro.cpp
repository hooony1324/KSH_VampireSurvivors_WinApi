#include "Intro.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>

#include "Counter.h"

Intro::Intro() 
{
}

Intro::~Intro() 
{
}


void Intro::Start()
{
	GameEngineRenderer* Renderer = CreateRenderer("Caution.bmp", 0, RenderPivot::CENTER ,GameEngineWindow::GetScale().Half());
	//Renderer->CreateAnimation("ddddd", "CautionOut", 0, 888, 0.1f, false);
	NextLevelOff();
}

void Intro::Update()
{
}

void Intro::Render()
{
}


bool Intro::IsCautionOut()
{

	return false;
}