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
}

void TitleLogo::Render()
{
	Rectangle(GameEngineWindow::GETDC(), 200, 200, 700, 500);
}

