#include "GameEngineString.h"
#include "GameEngineDebug.h"
#include <Windows.h>

GameEngineString::GameEngineString() 
{
}

GameEngineString::~GameEngineString() 
{
}


void GameEngineString::AnsiToUnicode(const std::string& _Text, std::wstring& _Out)
{
	int Size = MultiByteToWideChar(CP_ACP, 0, _Text.c_str(), static_cast<int>(_Text.size()), nullptr, 0);

	if (Size == 0)
	{
		MsgBoxAssert("스트링 변환에 실패했습니다.");
		return;
	}

	_Out.resize(Size);

	Size = MultiByteToWideChar(CP_ACP, 0, _Text.c_str(), static_cast<int>(_Text.size()), &_Out[0], Size);

	if (Size == 0)
	{
		MsgBoxAssert("스트링 변환에 실패했습니다.");
		return;
	}
}

// u8""

void GameEngineString::UniCodeToUTF8(const std::wstring& _Text, std::string& _Out)
{
	int Size = WideCharToMultiByte(CP_UTF8, 0, _Text.c_str(), static_cast<int>(_Text.size()), nullptr, 0, nullptr, nullptr);

	if (Size == 0)
	{
		MsgBoxAssert("스트링 변환에 실패했습니다.");
		return;
	}

	_Out.resize(Size);

	Size = WideCharToMultiByte(CP_UTF8, 0, _Text.c_str(), static_cast<int>(_Text.size()), &_Out[0], static_cast<int>(_Out.size()), nullptr, nullptr);

	if (Size == 0)
	{
		MsgBoxAssert("스트링 변환에 실패했습니다.");
		return;
	}

}

void GameEngineString::AnsiToUTF8(const std::string& _Text, std::string& _Out)
{
	std::wstring WString;

	AnsiToUnicode(_Text, WString);
	UniCodeToUTF8(WString, _Out);
}

std::string GameEngineString::AnsiToUTF8Return(const std::string& _Text)
{
	std::wstring WString;
	std::string Result;

	AnsiToUnicode(_Text, WString);
	UniCodeToUTF8(WString, Result);

	return Result;
}

std::wstring GameEngineString::StringToWStringReturn(const std::string& _Text)
{
	std::wstring Return;

	int Size = MultiByteToWideChar(CP_ACP, 0, _Text.c_str(), static_cast<int>(_Text.size()), nullptr, 0);

	if (Size == 0)
	{
		MsgBoxAssert("스트링 변환에 실패했습니다.");
		return L"";
	}

	Return.resize(Size);

	Size = MultiByteToWideChar(CP_ACP, 0, _Text.c_str(), static_cast<int>(_Text.size()), &Return[0], Size);

	if (Size == 0)
	{
		MsgBoxAssert("스트링 변환에 실패했습니다.");
		return L"";
	}

	return Return;
}
