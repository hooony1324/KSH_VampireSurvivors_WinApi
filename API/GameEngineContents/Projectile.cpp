#include "Projectile.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
//#include <GameEngineBase/GameEngineDebug.h>

#include "PlayerInfo.h"
Projectile::Projectile() 
{
}

Projectile::~Projectile() 
{
}

void Projectile::Start()
{
	CreateRenderer("sword.bmp");
	StartPos_ = PlayerInfo::GetInst()->GetCharacter()->Position_;
	ShootDir_ = float4::RIGHT;
}

void Projectile::Update()
{
	
	
	ProjPos_ += ShootDir_;
	// SetMove(ShootDir_ *GameEngineTime::GetDeltaTime() * 200.0f);
}
