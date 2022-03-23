#pragma once
#include "GameEnginePath.h"

// Ό³Έν :
class GameEngineFile : public GameEnginePath
{
public:
	// constrcuter destructer
	GameEngineFile();
	GameEngineFile(const std::string& _Path);
	GameEngineFile(std::filesystem::path _Path);
	GameEngineFile(const GameEngineFile& _Other);
	~GameEngineFile();

	// delete Function
	// GameEngineFile(GameEngineFile&& _Other) noexcept = delete;
	GameEngineFile& operator=(const GameEngineFile& _Other) = delete;
	GameEngineFile& operator=(GameEngineFile&& _Other) noexcept = delete;

protected:

private:

};

