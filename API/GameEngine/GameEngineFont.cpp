#include "GameEngineFont.h"
#include "GameEngine.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineBase/GameEngineString.h>
#include <Windows.h>

GameEngineFont::GameEngineFont() 
{
}

GameEngineFont::~GameEngineFont() 
{
	
}


// window system font ������ ������ ���ϸ� ������ �����մϴ�.
bool GameEngineFont::Load(const std::string& _Path)
{
	//LPCSTR FontSrc = "../Resources/UI/KO.ttf";
	if (0 == AddFontResourceA(_Path.c_str()))
	{
		MsgBoxAssert("����� �� ���� ��Ʈ�Դϴ�.");
	}

	GameEnginePath FilePath(_Path);

	FontName = FilePath.GetFileName();

	setlocale(LC_ALL, "");

	return true;
}

void GameEngineFont::Draw(const std::string& _Text, float4 _Postion, float _Size, float _Weight)
{
	hFont = CreateFontA(static_cast<int>(_Size), 0, 0, 0, static_cast<int>(_Weight), 0, 0, 0, JOHAB_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, FontName.c_str());

	if (nullptr == hFont)
	{
		MsgBoxAssert("����� �� ���� ��Ʈ�Դϴ�.");
	}

	std::wstring WText;
	GameEngineString::AnsiToUnicode(_Text, WText);

	oldFont = (HFONT)SelectObject(GameEngine::BackBufferDC(), hFont);
	TextOutW(GameEngine::BackBufferDC(), _Postion.ix(), _Postion.iy(), WText.c_str(), static_cast<int>(WText.size()));
	DeleteObject(hFont);
	(HFONT)SelectObject(GameEngine::BackBufferDC(), oldFont);
}