#include "Projectile.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
//#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngine/GameEngineCollision.h>

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
	ShootDir_ = float4::RIGHT; // shootdir 외부에서 세팅 가능해야됨
}

void Projectile::Update()
{
	ProjVec_ += ShootDir_ * GameEngineTime::GetDeltaTime() * 200.0f;
	SetPosition(StartPos_ + ProjVec_);
}
