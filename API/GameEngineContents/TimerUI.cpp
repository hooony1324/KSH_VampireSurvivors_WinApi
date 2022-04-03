#include "TimerUI.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
//#include <GameEngineBase/GameEngineDebug.h>

TimerUI::TimerUI() 
{
}

TimerUI::~TimerUI() 
{
}

void TimerUI::Start()
{
	SetPosition({ GameEngineWindow::GetScale().Half().x , 50 });
	SetScale({ 100, 10 });
}

void TimerUI::Update()
{
}

void TimerUI::Render()
{
	DebugRectRender();
}
