#include "GameEngineWriteFile.h"

GameEngineWriteFile::GameEngineWriteFile()
{

}

GameEngineWriteFile::GameEngineWriteFile(const std::string& _Path)
{
	Path_ = _Path;
}

GameEngineWriteFile::GameEngineWriteFile(std::filesystem::path _Path)
{
	Path_ = _Path;
}

GameEngineWriteFile::GameEngineWriteFile(const GameEngineWriteFile& _Other)
{
	Path_ = _Other.Path_;
}

GameEngineWriteFile::~GameEngineWriteFile()
{
}