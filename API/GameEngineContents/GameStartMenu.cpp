#include "GameStartMenu.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineInput.h>

#include "GameEnum.h"

GameStartMenu::GameStartMenu() 
{
}

GameStartMenu::~GameStartMenu() 
{
}

void GameStartMenu::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale(GameEngineWindow::GetScale());

	PressAnyKey_ = CreateRenderer("PressAnyKey.bmp", static_cast<int>(RENDER_ORDER::UI));
	PressAnyKey_->Off();
}

void GameStartMenu::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("SpaceBar"))
	{

	}
}

void GameStartMenu::Render()
{
}
