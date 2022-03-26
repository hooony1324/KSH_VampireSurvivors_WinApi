#include "VampireSurvivorsGame.h"
#include "PlayLevel.h"
#include "ResultLevel.h"
#include "TitleLevel.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngineBase/GameEngineInput.h>
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
	ChangeLevel("Title");


	// ��� ������ ������ Ű ����
	if (false == GameEngineInput::GetInst()->IsKey("MoveLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("MoveLeft", 'A');
		GameEngineInput::GetInst()->CreateKey("MoveRight", 'D');
		GameEngineInput::GetInst()->CreateKey("MoveUp", 'W');
		GameEngineInput::GetInst()->CreateKey("MoveDown", 'S');
		GameEngineInput::GetInst()->CreateKey("SpaceBar", VK_SPACE);
		GameEngineInput::GetInst()->CreateKey("Esc", VK_ESCAPE);

		// ChangeLevel(�ӽ�)
		GameEngineInput::GetInst()->CreateKey("ChangeLevelRight", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("ChangeLevelLeft", VK_LEFT);

		// Volume
		GameEngineInput::GetInst()->CreateKey("VolumeUp", VK_UP);
		GameEngineInput::GetInst()->CreateKey("VolumeDown", VK_DOWN);
	}
}

void VampireSurvivorsGame::GameLoop()
{
	if (true == GameEngineInput::GetInst()->IsDown("ChangeLevelRight"))
	{
		LevelIndex++;
		LevelIndex %= 3;
		GameEngine::ChangeLevel(Levels[LevelIndex]);
	}

	if (true == GameEngineInput::GetInst()->IsDown("ChangeLevelLeft"))
	{
		LevelIndex--;
		if (LevelIndex < 0)
		{
			LevelIndex = 2;
		}
		LevelIndex %= 3;
		GameEngine::ChangeLevel(Levels[LevelIndex]);
	}

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

		ResourcesDir.MoveParent("Resources");
	}

	// tilesets ���丮 Ž��
	{
		ResourcesDir.Move("tilesets");

		// �����ȿ� ��� ����(Ȯ���� .bmp) ����
		std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		}

		ResourcesDir.MoveParent("Resources");
	}

	// UI ���丮 Ž��
	{
		ResourcesDir.Move("UI");

		// �����ȿ� ��� ����(Ȯ���� .bmp) ����
		std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		}

		ResourcesDir.MoveParent("Resources");
	}

	
	
}
