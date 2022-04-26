#include "GameEngineFont.h"
#include "GameEngine.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineBase/GameEngineString.h>
#include <Windows.h>
#include <WinUser.h>

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

void GameEngineFont::Draw(const std::string& _Text, float4 _Postion, int TextColor, float _Size, float _Weight)
{
	hFont = CreateFontA(static_cast<int>(_Size), 0, 0, 0, static_cast<int>(_Weight), 0, 0, 0, JOHAB_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, FontName.c_str());

	if (nullptr == hFont)
	{
		MsgBoxAssert("����� �� ���� ��Ʈ�Դϴ�.");
	}

	std::wstring WText;
	GameEngineString::AnsiToUnicode(_Text, WText);

	//��Ʈ�� �����Լ�
	SetTextColor(GameEngine::BackBufferDC(), TextColor);
	SetBkMode(GameEngine::BackBufferDC(), 1);
	oldFont = (HFONT)SelectObject(GameEngine::BackBufferDC(), hFont);

	RECT NewRect = { _Postion.ix(), _Postion.iy(), 1280, 720 };
	DrawTextW(GameEngine::BackBufferDC(),
		WText.c_str(), static_cast<int>(WText.size()), &NewRect,
		DT_LEFT
	);
	DeleteObject(hFont);
	(HFONT)SelectObject(GameEngine::BackBufferDC(), oldFont);
}

void GameEngineFont::Draw(const std::wstring& _Text, float4 _Postion, int TextColor, float _Size, float _Weight)
{
	hFont = CreateFontA(static_cast<int>(_Size), 0, 0, 0, static_cast<int>(_Weight), 0, 0, 0, JOHAB_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, FontName.c_str());

	if (nullptr == hFont)
	{
		MsgBoxAssert("����� �� ���� ��Ʈ�Դϴ�.");
	}

	//��Ʈ�� �����Լ�
	SetTextColor(GameEngine::BackBufferDC(), TextColor);
	SetBkMode(GameEngine::BackBufferDC(), 1);
	oldFont = (HFONT)SelectObject(GameEngine::BackBufferDC(), hFont);
	RECT NewRect = { _Postion.ix(), _Postion.iy(), 1280, 720 };
	DrawTextW(GameEngine::BackBufferDC(),
		_Text.c_str(), static_cast<int>(_Text.size()), &NewRect,
		DT_LEFT
	);
	DeleteObject(hFont);
	(HFONT)SelectObject(GameEngine::BackBufferDC(), oldFont);
}