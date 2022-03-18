#include "VampireSurvivorsGame.h"
#include "PlayLevel.h"
#include "EndingLevel.h"
#include "TitleLevel.h"
#include <GameEngineBase/GameEngineWindow.h>

VampireSurvivorsGame::VampireSurvivorsGame() 
{
}

VampireSurvivorsGame::~VampireSurvivorsGame() 
{
}

void VampireSurvivorsGame::GameInit()
{
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 100, 100 }, { 1280, 800 });

	// Level을 맵 형태로 관리
	CreateLevel<TitleLevel>("Title");
	CreateLevel<PlayLevel>("Play");
	CreateLevel<EndingLevel>("Ending");
	ChangeLevel("Title");
}

void VampireSurvivorsGame::GameLoop()
{

}

void VampireSurvivorsGame::GameEnd()
{

}
