#pragma once
#include "GameEngineFile.h"

// Ό³Έν :
class GameEngineWriteFile : private GameEngineFile
{
public:
	// constrcuter destructer
	GameEngineWriteFile();
	GameEngineWriteFile(const std::string& _Path);
	GameEngineWriteFile(std::filesystem::path _Path);
	GameEngineWriteFile(const GameEngineWriteFile& _Other);
	~GameEngineWriteFile();

	// delete Function
	// GameEngineFile(GameEngineFile&& _Other) noexcept = delete;
	GameEngineWriteFile& operator=(const GameEngineWriteFile& _Other) = delete;
	GameEngineWriteFile& operator=(GameEngineWriteFile&& _Other) noexcept = delete;

protected:


private:
};

