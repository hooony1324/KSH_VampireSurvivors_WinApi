#pragma once
#include "GameEnginePath.h"

enum class OpenMode
{
	Read,
	Write,
};

// Ό³Έν :
class GameEngineFile : public GameEnginePath
{
public:
	// constrcuter destructer
	GameEngineFile();
	GameEngineFile(const char* _Path);
	GameEngineFile(std::filesystem::path _Path);
	GameEngineFile(const GameEngineFile& _Other);
	~GameEngineFile();

	// delete Function
	void Open(OpenMode _Mode);

	void ReadOpen() 
	{
		Open(OpenMode::Read);
	}

	void WriteOpen()
	{
		Open(OpenMode::Write);
	}

	void Close();

	void Create()
	{
		Open(OpenMode::Write);
		Close();
	}

protected:


private:
	FILE* FilePtr;
};

