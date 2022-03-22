#include "GameEngineImageManager.h"
#include "GameEngineBase/GameEngineDebug.h"

GameEngineImageManager* GameEngineImageManager::Inst_ = new GameEngineImageManager();

GameEngineImageManager::GameEngineImageManager() 
{
}

GameEngineImageManager::~GameEngineImageManager() 
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

GameEngineImage* GameEngineImageManager::Find(const std::string& _Name)
{
	std::map<std::string, GameEngineImage*>::iterator FindIter = AllRes.find(_Name);

	if (AllRes.end() == FindIter)
	{
		return nullptr;
	}

	return FindIter->second;
}

GameEngineImage* GameEngineImageManager::Create(const std::string& _Name, const float4& _Scale)
{
	if (AllRes.end() != AllRes.find(_Name))
	{
		MsgBoxAssert("이미 존재하는 이름의 이미지를 생성하려고 했습니다");
		return nullptr;
	}

	GameEngineImage* NewImage = new GameEngineImage();
	NewImage->SetName(_Name);

	if (false == NewImage->Create(_Scale))
	{
		delete NewImage;
		MsgBoxAssert((_Name + "이미지를 생성하는데 실패하였습니다").c_str());
		return nullptr;
	}

	AllRes.insert(std::make_pair(_Name, NewImage));

	return NewImage;
}

GameEngineImage* GameEngineImageManager::Create(const std::string& _Name, HDC _DC)
{
	if (AllRes.end() != AllRes.find(_Name))
	{
		MsgBoxAssert("이미 존재하는 이름의 이미지를 또 만들려고 했습니다.");
		return nullptr;
	}

	GameEngineImage* NewImage = new GameEngineImage();
	NewImage->SetName(_Name);

	if (false == NewImage->Create(_DC))
	{
		delete NewImage;
		MsgBoxAssert((_Name + "이미지를 생성하는데 실패했습니다.").c_str());
		return nullptr;
	}

	AllRes.insert(std::make_pair(_Name, NewImage));

	return NewImage;
}

GameEngineImage* GameEngineImageManager::Load(const std::string& _Path)
{
	// 무시
	// Create();

	return nullptr;
}

GameEngineImage* GameEngineImageManager::Load(const std::string& _Path, const std::string& _Name)
{
	if (AllRes.end() != AllRes.find(_Name))
	{
		MsgBoxAssert("이미 같은 이름의 이미지가 존재합니다.");
		return nullptr;
	}

	GameEngineImage* NewImage = new GameEngineImage();
	NewImage->SetName(_Name);

	if (false == NewImage->Load(_Path))
	{
		delete NewImage;
		MsgBoxAssert((_Name + "이미지를 생성하는데 실패했습니다.").c_str());
		return nullptr;
	}

	AllRes.insert(std::make_pair(_Name, NewImage));
	
	return NewImage;
}

