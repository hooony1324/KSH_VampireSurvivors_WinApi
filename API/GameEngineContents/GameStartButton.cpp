#include "GameStartButton.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
//#include <GameEngineBase/GameEngineDebug.h>

GameStartButton::GameStartButton() 
{
}

GameStartButton::~GameStartButton() 
{
}

void GameStartButton::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale({ 100 , 100 });

	
}

void GameStartButton::Update()
{
}

