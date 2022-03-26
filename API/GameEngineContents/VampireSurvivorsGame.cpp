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

	// 리소스 로드
	ResourceLoad();

	// Level을 맵 형태로 관리
	CreateLevel<TitleLevel>("Title");
	CreateLevel<PlayLevel>("Play");
	CreateLevel<ResultLevel>("Result");
	ChangeLevel("Title");


	// 모든 레벨을 통합한 키 세팅
	if (false == GameEngineInput::GetInst()->IsKey("MoveLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("MoveLeft", 'A');
		GameEngineInput::GetInst()->CreateKey("MoveRight", 'D');
		GameEngineInput::GetInst()->CreateKey("MoveUp", 'W');
		GameEngineInput::GetInst()->CreateKey("MoveDown", 'S');
		GameEngineInput::GetInst()->CreateKey("SpaceBar", VK_SPACE);
		GameEngineInput::GetInst()->CreateKey("Esc", VK_ESCAPE);

		// ChangeLevel(임시)
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
	
	// characters 디렉토리 탐색
	{
		ResourcesDir.Move("characters");

		// 폴더안에 모든 파일(확장자 .bmp) 얻어옴
		std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		}

		ResourcesDir.MoveParent("Resources");
	}

	// tilesets 디렉토리 탐색
	{
		ResourcesDir.Move("tilesets");

		// 폴더안에 모든 파일(확장자 .bmp) 얻어옴
		std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		}

		ResourcesDir.MoveParent("Resources");
	}

	// UI 디렉토리 탐색
	{
		ResourcesDir.Move("UI");

		// 폴더안에 모든 파일(확장자 .bmp) 얻어옴
		std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		}

		ResourcesDir.MoveParent("Resources");
	}

	
	
}
