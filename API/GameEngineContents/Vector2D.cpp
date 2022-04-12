#include "Vector2D.h"

#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineActor.h>
#include <string>

void Vector2D::DebugVectorRender(GameEngineActor* _Actor)
{

	HDC hdc = GameEngine::GetInst().BackBufferDC();
	TCHAR Buffer[30] = "";
	sprintf_s(Buffer, "Pos { %d, %d } ", _Actor->GetPosition().ix(), _Actor->GetPosition().iy());

	SetTextColor(hdc, RGB(255, 255, 255));
	SetBkMode(hdc, TRANSPARENT);
	TextOutA(hdc, _Actor->GetCameraEffectPosition().ix(), _Actor->GetCameraEffectPosition().iy() - 50, Buffer, strlen(Buffer));
}

Vector2D::Vector2D()
{
}

Vector2D::~Vector2D() 
{
}

