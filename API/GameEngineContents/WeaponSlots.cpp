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
	GameEngineRenderer* Slot = CreateRenderer("WeaponSlots.bmp");
	SetPosition(Slot->GetScale().Half() + float4{ 0, 31 });
	SetScale(Slot->GetScale());
	Slot->CameraEffectOff();
}

void WeaponSlots::Update()
{

}

void WeaponSlots::Render()
{
}
