#include "GameEngineFile.h"
#include "GameEngineDebug.h"

GameEngineFile::GameEngineFile() 
	: FilePtr(nullptr)
{

}

GameEngineFile::GameEngineFile(const char* _Path)
	: FilePtr(nullptr)
{
	Path_ = _Path;
}

GameEngineFile::GameEngineFile(std::filesystem::path _Path)
	: FilePtr(nullptr)
{
	Path_ = _Path;
}

GameEngineFile::GameEngineFile(const GameEngineFile& _Other) 
	: FilePtr(nullptr)
{
	Path_ = _Other.Path_;
}

GameEngineFile::~GameEngineFile() 
{
	GameEngineFile::Close();
}

void GameEngineFile::Close()
{
	if (nullptr != FilePtr)
	{
		fclose(FilePtr);
		FilePtr = nullptr;
	}
}

// "text"
// 

void GameEngineFile::Open(OpenMode _Mode)
{
	// b냐 t냐에 따라서 파일이 저장되었을때의 최종적인 형식이 달라지게 된다.
	std::string OpenMode = "";
	switch (_Mode)
	{
	case OpenMode::Read:
		OpenMode = "rb";
		break;
	case OpenMode::Write:
		OpenMode = "wb";
		break;
	default:
		break;
	}

	fopen_s(&FilePtr, Path_.string().c_str(), OpenMode.c_str());

	if (nullptr == FilePtr)
	{
		MsgBoxAssert("파일이 정상적으로 열리지 않았습니다.");
	}
}