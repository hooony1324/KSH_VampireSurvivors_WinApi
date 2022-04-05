#pragma once
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineImage.h"
#include <Windows.h>
#include <vector>

// Ό³Έν :
class GameEngineFolderImage : public GameEngineNameObject
{
public:
	// constrcuter destructer
	GameEngineFolderImage();
	~GameEngineFolderImage();

	// delete Function
	GameEngineFolderImage(const GameEngineFolderImage& _Other) = delete;
	GameEngineFolderImage(GameEngineFolderImage&& _Other) noexcept = delete;
	GameEngineFolderImage& operator=(const GameEngineFolderImage& _Other) = delete;
	GameEngineFolderImage& operator=(GameEngineFolderImage&& _Other) noexcept = delete;

	bool Load(const std::string& _Path);

	inline GameEngineImage* GetImage(size_t _Index) const
	{
		return Images_[_Index];
	}

private:
	std::vector<GameEngineImage*> Images_;
};

