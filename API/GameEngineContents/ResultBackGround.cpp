#include "ResultBackGround.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
//#include <GameEngineBase/GameEngineDebug.h>

ResultBackGround::ResultBackGround() 
{
}

ResultBackGround::~ResultBackGround() 
{
}

void ResultBackGround::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale(GameEngineWindow::GetScale());

	CreateRenderer("introBG.bmp");
}

void ResultBackGround::Update()
{
}

void ResultBackGround::Render()
{
}
