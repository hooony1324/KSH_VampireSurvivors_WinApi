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

	// ���ҽ� �ε�
	ResourceLoad();

	// Level�� �� ���·� ����
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
