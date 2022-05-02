#pragma once
#include "GameEngineFile.h"

// Ό³Έν :
class GameEngineReadFile : private GameEngineFile
{
public:
	// constrcuter destructer
	GameEngineReadFile();
	GameEngineReadFile(const std::string& _Path);
	GameEngineReadFile(std::filesystem::path _Path);
	GameEngineReadFile(const GameEngineReadFile& _Other);
	~GameEngineReadFile();

	// delete Function
	// GameEngineFile(GameEngineFile&& _Other) noexcept = delete;
	GameEngineReadFile& operator=(const GameEngineReadFile& _Other) = delete;
	GameEngineReadFile& operator=(GameEngineReadFile&& _Other) noexcept = delete;

protected:


private:
};

