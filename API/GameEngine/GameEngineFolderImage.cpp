#include "GameEngineFolderImage.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include "GameEngineImageManager.h"


GameEngineFolderImage::GameEngineFolderImage()
{

}

GameEngineFolderImage::~GameEngineFolderImage()
{
	for (size_t i = 0; i < Images_.size(); i++)
	{
		delete Images_[i];
		Images_[i] = nullptr;
	}
}

bool GameEngineFolderImage::Load(const std::string& _Path)
{
	// ���丮, ���ҽ����� ��� ����
	GameEngineDirectory ResourcesDir = GameEngineDirectory(_Path);;

	// �����ȿ� ��� �̹��� ������ ã�´�.
	std::vector<GameEngineFile> PlayerImageFileList = ResourcesDir.GetAllFile("bmp");

	Images_.reserve(PlayerImageFileList.size());

	for (size_t i = 0; i < PlayerImageFileList.size(); ++i)
	{
		GameEngineImage* Image = new GameEngineImage();

		if (false == Image->Load(PlayerImageFileList[i].GetFullPath()))
		{
			MsgBoxAssert("���� �̹��� �ε��� ������ �̹����� �����մϴ�.");
		}

		Images_.push_back(Image);
	}

	return true;
}
