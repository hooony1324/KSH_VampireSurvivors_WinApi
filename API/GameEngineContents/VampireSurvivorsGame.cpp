#include "VampireSurvivorsGame.h"
#include "PlayLevel.h"
#include "ResultLevel.h"
#include "TitleLevel.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>

VampireSurvivorsGame::VampireSurvivorsGame() 
{
}

VampireSurvivorsGame::~VampireSurvivorsGame() 
{
}

void VampireSurvivorsGame::GameInit()
{
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 100, 100 }, { 1280, 800 });

	// 리소스 로드
	ResourceLoad();

	// Level을 맵 형태로 관리
	CreateLevel<TitleLevel>("Title");
	CreateLevel<PlayLevel>("Play");
	CreateLevel<ResultLevel>("Result");
	ChangeLevel("Play");
}

void VampireSurvivorsGame::GameLoop()
{

}

void VampireSurvivorsGame::GameEnd()
{

}

void VampireSurvivorsGame::ResourceLoad()
{
	// TitleLevel
	GameEngineImageManager::GetInst()->Load("../Resources/introBG.bmp", "introBG.bmp");

	// PlayLevel
	GameEngineImageManager::GetInst()->Load("../Resources/Old3_01.bmp", "Old_idle.bmp");

	// ResultLevel
	

}
