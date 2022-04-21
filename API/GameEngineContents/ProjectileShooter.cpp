#include "ProjectileShooter.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>

#include "GameEnum.h"
#include "Vector2D.h"
#include "GameInfo.h"

GameEngineRandom Random;

ProjectileShooter::ProjectileShooter()
	: BT_(BulletType::FLAME_BLUE)
	, Projectile_(nullptr)
	, ShootAble_(false)
	, isShoot_(false)
	, FireShootDir_(float4{1, -1})

{
}

ProjectileShooter::~ProjectileShooter() 
{
}

void ProjectileShooter::Start()
{

}

void ProjectileShooter::Update()
{

}

void ProjectileShooter::SetShooter(BulletType _BT, int _BulletCount, float _Interval, float _CoolTime, float _WaitTime)
{
	InitBulletCount_ = _BulletCount;
	InitInterval_ = _Interval;
	InitCoolTime_ = _CoolTime;
	BT_ = _BT;
	isShoot_ = false;
	
	CoolTimeCount_ = _WaitTime;
	BulletCount_ = InitBulletCount_;
	IntervalCount_ = InitInterval_;
	PlayerMoveDir_ = float4::RIGHT;
}

void ProjectileShooter::Shooting(float _DeltaTime, float4 _PlayerPos, float4 _MonsterPos, float4 _PlayerMoveDir)
{
	if (_PlayerMoveDir.x != 0.0f || _PlayerMoveDir.y != 0.0f)
	{
		PlayerMoveDir_ = _PlayerMoveDir;
	}

	// 일시정지
	if (0.1f > GameEngineTime::GetInst()->GetTimeScale(static_cast<int>(TIME_GROUP::WEAPON)))
	{
		return;
	}


	// 쿨타임 아니면
	if (0 < CoolTimeCount_)
	{
		CoolTimeCount_ -= _DeltaTime;
		return;
	}

	// 쏜 상태(인터벌 타임에 진입하면 isShoot는 false상태)
	if (true == isShoot_ || 0 < IntervalCount_)
	{
		IntervalCount_ -= _DeltaTime;
		isShoot_ = false;
		return;
	}

	// 쏜 상태 아니면, 인터벌이 끝났으면
	
	// 총알이 없으면
	if (BulletCount_ == 0)
	{
		BulletCount_ = InitBulletCount_;
		CoolTimeCount_ = InitCoolTime_;
		isShoot_ = false;
		IntervalCount_ = 0;
		return;
	}

	// 총알 있으면 쏜다
	PlayerPos_ = _PlayerPos;
	MonsterPos_ = _MonsterPos;
	switch (BT_)
	{
	case BulletType::KNIFE:
		ShootKnife();
		break;
	case BulletType::FLAME_BLUE:
		ShootMagic();
		break;
	case BulletType::FLAME_RED:
		ShootFire();
		break;
	default:
		break;
	}

	return;
}

void ProjectileShooter::ShootKnife()
{
	// Knife
	Projectile* Bullet = GetLevel()->CreateActor<Projectile>(static_cast<int>(ACTOR_ORDER::PLAYER), "Bullet");
	float4 RandomPos = float4{ Random.RandomFloat(PlayerPos_.x - 25, PlayerPos_.x + 25), Random.RandomFloat(PlayerPos_.y - 25, PlayerPos_.y + 25) };
	Bullet->SetPosition(RandomPos);
	Bullet->SetType(BT_);
	Bullet->SetDamage(50);
	Bullet->SetDir(PlayerMoveDir_);


	BulletCount_ -= 1;
	isShoot_ = true;
	IntervalCount_ = InitInterval_;
}

void ProjectileShooter::ShootMagic()
{
	// MagicWand
	// 총알 쏘고 isShoot = true
	Projectile* Bullet = GetLevel()->CreateActor<Projectile>(static_cast<int>(ACTOR_ORDER::PLAYER), "Bullet");
	Bullet->SetType(BT_);
	Bullet->SetDamage(100);
	Bullet->SetDir(Vector2D::GetDirection(PlayerPos_, MonsterPos_));
	Bullet->SetPosition(PlayerPos_);

	BulletCount_ -= 1;
	isShoot_ = true;
	IntervalCount_ = InitInterval_;
}

void ProjectileShooter::ShootFire()
{
	FireShootDir_ = Vector2D::GetDirection(PlayerPos_, MonsterPos_);

	for (int i = 0; i < 3; i++)
	{
		Projectile* Bullet = GetLevel()->CreateActor<Projectile>(static_cast<int>(ACTOR_ORDER::PLAYER), "Bullet");
		Bullet->SetType(BT_);
		Bullet->SetDamage(100);
		FireShootDir_.x *= 0.8f;
		FireShootDir_.y *= 1.2f;
		FireShootDir_.Normal2D();
		Bullet->SetDir(FireShootDir_);
		Bullet->SetPosition(PlayerPos_);

	}

	BulletCount_ -= 1;
	isShoot_ = true;
	IntervalCount_ = InitInterval_;
	
}
