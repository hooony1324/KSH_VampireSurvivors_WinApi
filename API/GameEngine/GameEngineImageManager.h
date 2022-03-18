#pragma once
#include "GameEngineImage.h"
#include <GameEngineBase/GameEngineMath.h>
#include <map>

// Ό³Έν :
class GameEngineImageManager
{
private:
	static GameEngineImageManager* Inst_;

public:
	static GameEngineImageManager* GetInst()
	{
		return Inst_;
	}

	static void Destroy()
	{
		if (nullptr == Inst_)
		{
			return;
		}

		delete Inst_;
		Inst_ = nullptr;
	}

	GameEngineImage* Create(const std::string& _Name, float4 _Scale);

	GameEngineImage* Create(const std::string& _Name, HDC _DC);

private:
	// constrcuter destructer
	GameEngineImageManager();
	~GameEngineImageManager();

	// delete Function
	GameEngineImageManager(const GameEngineImageManager& _Other) = delete;
	GameEngineImageManager(GameEngineImageManager&& _Other) noexcept = delete;
	GameEngineImageManager& operator=(const GameEngineImageManager& _Other) = delete;
	GameEngineImageManager& operator=(GameEngineImageManager&& _Other) noexcept = delete;

protected:

private:
	std::map<std::string, GameEngineImage*> AllRes;
};

