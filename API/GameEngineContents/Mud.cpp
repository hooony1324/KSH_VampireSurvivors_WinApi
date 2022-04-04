#include "Mud.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
//#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

Mud::Mud() 
{
}

Mud::~Mud() 
{

}

void Mud::KillEnemy()
{
	MudCol_->Death();
	GameEngineUpdateObject::Death();
}

void Mud::Start()
{
	Mud_ = CreateRenderer("Mud_0.bmp");
	SetPosition({ 1000, 600 });
	SetScale({ 100, 100 });

	MudCol_ = CreateCollision("Monster", { 40, 40 });
	
}

void Mud::Render()
{
}
