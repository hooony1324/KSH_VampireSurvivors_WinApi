#include "GameEngineImageManager.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineString.h>
#include <GameEngineBase/GameEnginePath.h>

GameEngineImageManager* GameEngineImageManager::Inst_ = new GameEngineImageManager();

GameEngineImageManager::GameEngineImageManager()
{
}

GameEngineImageManager::~GameEngineImageManager()
{
	{
		std::map<std::string, GameEngineFolderImage*>::iterator StartIter = AllFolderRes.begin();
		std::map<std::string, GameEngineFolderImage*>::iterator EndIter = AllFolderRes.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			if (nullptr != StartIter->second)
			{
				delete StartIter->second;
				StartIter->second = nullptr;
			}
		}
	}


	{
		std::map<std::string, GameEngineImage*>::iterator StartIter = AllRes.begin();
		std::map<std::string, GameEngineImage*>::iterator EndIter = AllRes.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			if (nullptr != StartIter->second)
			{
				delete StartIter->second;
				StartIter->second = nullptr;
			}
		}
	}
}

GameEngineImage* GameEngineImageManager::Find(const std::string& _Name)
{
	std::string EngineName = GameEngineString::ToUpperReturn(_Name);

	std::map<std::string, GameEngineImage*>::iterator FindIter = AllRes.find(EngineName);

	if (AllRes.end() == FindIter)
	{
		// MsgBoxAssert("�̹� �����ϴ� �̸��� �̹����� �� ������� �߽��ϴ�.");
		return nullptr;
	}

	return FindIter->second;
}

GameEngineImage* GameEngineImageManager::Create(const std::string& _Name, HDC _DC)
{
	std::string EngineName = GameEngineString::ToUpperReturn(_Name);

	if (AllRes.end() != AllRes.find(EngineName))
	{
		MsgBoxAssert("�̹� �����ϴ� �̸��� �̹����� �� ������� �߽��ϴ�.");
		return nullptr;
	}

	GameEngineImage* NewImage = new GameEngineImage();
	NewImage->SetName(EngineName);

	if (false == NewImage->Create(_DC))
	{
		delete NewImage;
		MsgBoxAssert((EngineName + "�̹����� �����ϴµ� �����߽��ϴ�.").c_str());
		return nullptr;
	}

	AllRes.insert(std::make_pair(EngineName, NewImage));

	return NewImage;
}

GameEngineImage* GameEngineImageManager::Create(const std::string& _Name, const float4& _Scale)
{
	std::string EngineName = GameEngineString::ToUpperReturn(_Name);
	if (AllRes.end() != AllRes.find(EngineName))
	{
		MsgBoxAssert("�̹� �����ϴ� �̸��� �̹����� �� ������� �߽��ϴ�.");
		return nullptr;
	}

	GameEngineImage* NewImage = new GameEngineImage();
	NewImage->SetName(EngineName);

	if (false == NewImage->Create(_Scale))
	{
		delete NewImage;
		MsgBoxAssert((EngineName + "�̹����� �����ϴµ� �����߽��ϴ�.").c_str());
		return nullptr;
	}

	AllRes.insert(std::make_pair(EngineName, NewImage));

	return NewImage;
}

GameEngineImage* GameEngineImageManager::Load(const std::string& _Path)
{
	GameEnginePath NewPath = GameEnginePath(_Path);
	return GameEngineImageManager::Load(_Path, NewPath.GetFileName());	//��ο� �����̸�(ex.idle.bmp)�� Map�� key,value�� �ֱ����� ���� �Ѱ��ش�.
}

GameEngineImage* GameEngineImageManager::Load(const std::string& _Path, const std::string& _Name)
{
	std::string EngineName = GameEngineString::ToUpperReturn(_Name);
	if (AllRes.end() != AllRes.find(EngineName))
	{
		MsgBoxAssert("�̹� �����ϴ� �̸��� �̹����� �� ������� �߽��ϴ�.");
		return nullptr;
	}

	GameEngineImage* NewImage = new GameEngineImage();
	NewImage->SetName(EngineName);

	if (false == NewImage->Load(_Path))
	{
		delete NewImage;
		MsgBoxAssert((_Name + "�̹����� �����ϴµ� �����߽��ϴ�.").c_str());
		return nullptr;
	}

	AllRes.insert(std::make_pair(EngineName, NewImage));

	return NewImage;
}

//////////////////////////////////////////////////////// ���� �̹���

GameEngineFolderImage* GameEngineImageManager::FolderImageFind(const std::string& _Name)
{
	std::string EngineName = GameEngineString::ToUpperReturn(_Name);

	std::map<std::string, GameEngineFolderImage*>::iterator FindIter = AllFolderRes.find(EngineName);

	if (AllFolderRes.end() == FindIter)
	{
		// MsgBoxAssert("�̹� �����ϴ� �̸��� �̹����� �� ������� �߽��ϴ�.");
		return nullptr;
	}

	return FindIter->second;
}

GameEngineFolderImage* GameEngineImageManager::FolderImageLoad(const std::string& _Path)
{
	GameEnginePath NewPath = GameEnginePath(_Path);
	return GameEngineImageManager::FolderImageLoad(_Path, NewPath.GetFileName());	//��ο� �����̸�(ex.idle.bmp)�� Map�� key,value�� �ֱ����� ���� �Ѱ��ش�.

}

GameEngineFolderImage* GameEngineImageManager::FolderImageLoad(const std::string& _Path, const std::string& _Name)
{
	std::string EngineName = GameEngineString::ToUpperReturn(_Name);
	if (AllFolderRes.end() != AllFolderRes.find(EngineName))
	{
		MsgBoxAssert("�̹� �����ϴ� �̸��� ���� �̹����� �� ������� �߽��ϴ�.");
		return nullptr;
	}

	GameEngineFolderImage* NewImage = new GameEngineFolderImage();
	NewImage->SetName(EngineName);

	if (false == NewImage->Load(_Path))
	{
		delete NewImage;
		MsgBoxAssert((_Name + "�̹����� �����ϴµ� �����߽��ϴ�.").c_str());
		return nullptr;
	}

	AllFolderRes.insert(std::make_pair(EngineName, NewImage));

	return NewImage;
}












