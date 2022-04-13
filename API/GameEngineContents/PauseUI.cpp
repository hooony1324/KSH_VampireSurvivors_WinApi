#include "PauseUI.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineDebug.h>

PauseUI::PauseUI() 
{
}

PauseUI::~PauseUI() 
{
}

void PauseUI::Start()
{
	SetScale({ 500, 500 });
	SetPosition(GameEngineWindow::GetScale().Half());
}

void PauseUI::Update()
{
}

void PauseUI::Render()
{
	DebugRectRender();
}
