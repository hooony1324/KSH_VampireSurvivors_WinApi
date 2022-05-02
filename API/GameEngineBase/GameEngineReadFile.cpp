#include "GameEngineReadFile.h"

GameEngineReadFile::GameEngineReadFile()
{

}

GameEngineReadFile::GameEngineReadFile(const std::string& _Path)
{
	Path_ = _Path;
}

GameEngineReadFile::GameEngineReadFile(std::filesystem::path _Path)
{
	Path_ = _Path;
}

GameEngineReadFile::GameEngineReadFile(const GameEngineReadFile& _Other)
{
	Path_ = _Other.Path_;
}

GameEngineReadFile::~GameEngineReadFile()
{
}