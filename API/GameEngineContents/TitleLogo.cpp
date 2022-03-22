#include "TitleLogo.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineWindow.h>

TitleLogo::TitleLogo() 
{
}

TitleLogo::~TitleLogo() 
{
}

void TitleLogo::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale({ 200, 200 });
}

void TitleLogo::Render()
{
	DebugRectRender();
}

