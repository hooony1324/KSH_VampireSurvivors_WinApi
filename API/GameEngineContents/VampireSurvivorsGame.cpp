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
		GameEngineInput::GetInst()->CreateKey("ChangeLevelNext", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("ChangeLevelPrev", VK_LEFT);

		// Volume
		GameEngineInput::GetInst()->CreateKey("VolumeUp", VK_UP);
		GameEngineInput::GetInst()->CreateKey("VolumeDown", VK_DOWN);

		// �����ص� ��
		GameEngineInput::GetInst()->CreateKey("KillPlayer", 'K');
		GameEngineInput::GetInst()->CreateKey("PlayerDamaged", 'P');

	}
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

	std::string Directories[] = {"characters", "tilesets", "illustrations", "vfx"};
	
	for (std::string& Dir : Directories)
	{
		ResourcesDir.Move(Dir);
		std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		}

		ResourcesDir.MoveParent("Resources");
	}
	
}
