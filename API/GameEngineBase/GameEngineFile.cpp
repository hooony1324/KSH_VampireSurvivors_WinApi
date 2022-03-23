#include "GameEngineFile.h"

GameEngineFile::GameEngineFile()
{

}

GameEngineFile::GameEngineFile(const std::string& _Path)
{
	Path_ = _Path;
}

GameEngineFile::GameEngineFile(std::filesystem::path _Path)
{
	Path_ = _Path;
}

GameEngineFile::GameEngineFile(const GameEngineFile& _Other)
{
	Path_ = _Other.Path_;
}

GameEngineFile::~GameEngineFile()
{
}