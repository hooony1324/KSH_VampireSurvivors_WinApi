#include "KillCountUI.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
//#include <GameEngineBase/GameEngineDebug.h>

KillCountUI::KillCountUI() 
{
}

KillCountUI::~KillCountUI() 
{
}

void KillCountUI::Start()
{
	SetPosition(float4{GameEngineWindow::GetScale().Half().x, 0 } + float4{410, 45});
	SetScale(float4{60, 28});



}

void KillCountUI::Update()
{
}

void KillCountUI::Render()
{
}


// 폰트 가져오기
/*HDC hdc = GameEngine::GetInst().BackBufferDC();

LPCSTR FontSrc = "../Resources/UI/KO.ttf";
AddFontResourceA(FontSrc);


HFONT hFont, oldFont;
int Size = 12;
int Weight = 800;
hFont = CreateFont(Size, 0, 0, 0, Weight, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("KO"));
oldFont = (HFONT)SelectObject(hdc, hFont);

TCHAR Buffer[30] = "";
sprintf_s(Buffer, "Pos { %d, %d } 한글", GetPosition().ix(), GetPosition().iy());

SetTextColor(hdc, RGB(255, 255, 255));
SetBkMode(hdc, TRANSPARENT);
TextOutA(hdc, 500, 500, Buffer, strlen(Buffer));*/
