#include "Projectile.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
//#include <GameEngineBase/GameEngineDebug.h>

Projectile::Projectile() 
{
}

Projectile::~Projectile() 
{
}

void Projectile::Start()
{
	CreateRenderer("sword.bmp");
}

void Projectile::Update()
{
	SetMove(float4{ 2, 1 } *GameEngineTime::GetDeltaTime() * 200.0f);
}
