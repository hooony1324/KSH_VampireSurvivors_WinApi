#include "Projectile.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
//#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>

#include "PlayerInfo.h"
#include "Vector2D.h"

#include <string>

std::vector<std::string> ProjectileList = { "Sword.bmp", "ProjectileHoly1.bmp", "ProjectileFlameRed.bmp" };

Projectile::Projectile() 
	: ProjImage_(nullptr)
	, ShootDir_(float4::ZERO)
	, ProjVec_(float4::ZERO)
{
}

Projectile::~Projectile() 
{
}

void Projectile::SetType(BulletType _BT)
{
	ProjImage_ = CreateRenderer(ProjectileList[static_cast<int>(_BT)]);
	CreateCollision("Bullet", ProjImage_->GetScale());
}



void Projectile::Start()
{
	SetScale({ 20, 20 });
	ShootDir_ = float4::RIGHT;
	Damage_ = 10;
}

void Projectile::Update()
{
	SetMove(ShootDir_ * GameEngineTime::GetDeltaTime() * 300.0f);
}

void Projectile::Render()
{
	Vector2D::DebugVectorRender(this);
}
