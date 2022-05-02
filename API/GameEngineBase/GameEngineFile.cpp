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
	// b�� t�Ŀ� ���� ������ ����Ǿ������� �������� ������ �޶����� �ȴ�.
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
		MsgBoxAssert("������ ���������� ������ �ʾҽ��ϴ�.");
	}
}