#include "LevelUI.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
//#include <GameEngineBase/GameEngineDebug.h>

#include "ObjectEnum.h"
#include <GameEngine/GameEngineRenderer.h>
#include "GameInfo.h"
#include <string>


#include "Vector2D.h"


LevelUI::LevelUI()
{
}

LevelUI::~LevelUI() 
{
}

void LevelUI::Start()
{
	SetPosition({ GameEngineWindow::GetScale().x - 50, 0 });
	SetScale({ 100, 30 });
	BackBufferDC_ = GameEngine::GetInst().BackBufferDC();

	// 폰트 설정
	LPCSTR FontSrc = "../Resources/UI/KO.ttf";
	AddFontResourceA(FontSrc);

	HFONT hFont, oldFont;
	int Size = 28;
	int Weight = 900;
	hFont = CreateFont(Size, 0, 0, 0, Weight, 0, 0, 0, JOHAB_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("KO.ttf"));
	oldFont = (HFONT)SelectObject(BackBufferDC_, hFont);

	SetTextColor(BackBufferDC_, RGB(255, 255, 255));
	SetBkMode(BackBufferDC_, TRANSPARENT);
}

void LevelUI::Update()
{
	PlayerLevel_ = GameInfo::GetPlayerInfo()->Level_;
}

void LevelUI::Render()
{
	TCHAR Buffer[30] = "";
	sprintf_s(Buffer, "LV %d", PlayerLevel_);

	int StrLength = strlen(Buffer) - 4; 
	int Space = 10 * StrLength;

	TextOutA(BackBufferDC_, GetPosition().x - Space, GetPosition().y, Buffer, strlen(Buffer));

}
