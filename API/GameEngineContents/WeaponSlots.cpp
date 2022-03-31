#include "WeaponSlots.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
//#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngine/GameEngineRenderer.h>

WeaponSlots::WeaponSlots() 
{
}

WeaponSlots::~WeaponSlots() 
{
}

void WeaponSlots::Start()
{
	SetPosition({ 0, 36 });
	SetScale({ 100, 100 });

	GameEngineRenderer* Slot = CreateRenderer("WeaponSlots.bmp");
	Slot->SetPivot(Slot->GetScale().Half());
	Slot->CameraEffectOff();
}

void WeaponSlots::Update()
{

}

void WeaponSlots::Render()
{
}
