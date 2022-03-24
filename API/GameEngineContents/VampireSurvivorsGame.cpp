#include "VampireSurvivorsGame.h"
#include "PlayLevel.h"
#include "ResultLevel.h"
#include "TitleLevel.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
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
	GameEngineDirectory ResourcesDir;
	ResourcesDir.MoveParent("API");
	ResourcesDir.Move("Resources");
	
	// characters ���丮 Ž��
	{
		ResourcesDir.Move("characters");

		// �����ȿ� ��� ����(Ȯ���� .bmp) ����
		std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		}
	}

	// tilesets ���丮 Ž��
	ResourcesDir.MoveParent("Resources");
	{
		ResourcesDir.Move("tilesets");

		// �����ȿ� ��� ����(Ȯ���� .bmp) ����
		std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		}
	}
	
	
}
