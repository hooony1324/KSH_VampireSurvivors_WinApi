#include "Projectile.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
//#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>
#include <string>

#include "Vector2D.h"
#include "ObjectEnum.h"

std::vector<std::string> ProjectileList = { "Sword.bmp", "ProjectileHoly1.bmp", "ProjectileFlameRed.bmp" };

Projectile::Projectile()
	: ProjImage_(nullptr)
	, ShootDir_(float4::ZERO)
	, Damage_(10)
	, Speed_(200)
	, Duration_(5)	// 지속시간
{
}

Projectile::~Projectile() 
{

}

void Projectile::Start()
{
	SetScale({ 20, 20 });
	ShootDir_ = float4::RIGHT;
	Damage_ = 10;

	
}

void Projectile::Update()
{
	float DeltaTime = GameEngineTime::GetDeltaTime(static_cast<int>(TIME_GROUP::WEAPON));
	SetMove(ShootDir_ * DeltaTime * Speed_);
	Duration_ -= DeltaTime;


	if (0.05f > Duration_)
	{
		Death();
	}
}

void Projectile::Render()
{
}


void Projectile::SetType(BulletType _BT)
{
	ProjImage_ = CreateRenderer(ProjectileList[static_cast<int>(_BT)]);
	ProjCol_ = CreateCollision("PlayerAttack", float4{9, 9});

	// 세부 설정
	switch (_BT)
	{
	case BulletType::KNIFE:
	{
		GameEngineSound::SoundPlayOneShot("ProjectileKnife.mp3", 0);
		auto val = ShootDir_;
		ProjCol_->SetPivot(ShootDir_ * 18);
		Speed_ = 500.0f;
		break;
	}
	case BulletType::FLAME_BLUE:
	{
		// 발사 효과음
		GameEngineSound::SoundPlayOneShot("ProjectileMagic.mp3", 0);
		Speed_ = 400.0f;
		break;
	}
	case BulletType::FLAME_RED:
		Speed_ = 300.0f;
		break;

	}

}