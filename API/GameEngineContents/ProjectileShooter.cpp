#include "ProjectileShooter.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>

#include "GameEnum.h"
#include "Vector2D.h"
#include "GameInfo.h"
#include "Skill_Stat.h"


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

void ProjectileShooter::SetShooter(SkillType _SkillType, float _WaitTime)
{
	SkillLevel_ = GameInfo::GetPlayerInfo()->SkillLevelInfo_[static_cast<int>(SkillType_)];

	//탄수		인터벌		쿨타임		데미지		속도			지속시간 
	SkillType_ = _SkillType;
	InitBulletCount_ = STAT_SHOOTER[static_cast<int>(SkillType_)][SkillLevel_][0];
	InitInterval_ = STAT_SHOOTER[static_cast<int>(SkillType_)][SkillLevel_][1];
	InitCoolTime_ = STAT_SHOOTER[static_cast<int>(SkillType_)][SkillLevel_][2];
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
	switch (SkillType_)
	{
	case SkillType::KNIFE:
		ShootKnife();
		break;
	case SkillType::MAGICWAND:
		ShootMagic();
		break;
	case SkillType::FIREWAND:
		ShootFire();
		break;
	default:
		break;
	}

	return;
}

void ProjectileShooter::SetSkillStat(Projectile* _Bullet)
{
	//탄수		인터벌		쿨타임		데미지		속도			지속시간 
	SkillLevel_ = GameInfo::GetPlayerInfo()->SkillLevelInfo_[static_cast<int>(SkillType_)];
	InitBulletCount_ = STAT_SHOOTER[static_cast<int>(SkillType_)][SkillLevel_][0];
	InitInterval_ = STAT_SHOOTER[static_cast<int>(SkillType_)][SkillLevel_][1];
	InitCoolTime_ = STAT_SHOOTER[static_cast<int>(SkillType_)][SkillLevel_][2];

	_Bullet->SetDamage(STAT_SHOOTER[static_cast<int>(SkillType_)][SkillLevel_][3]);
	_Bullet->SetSpeed(STAT_SHOOTER[static_cast<int>(SkillType_)][SkillLevel_][4]);
	_Bullet->SetDuration(STAT_SHOOTER[static_cast<int>(SkillType_)][SkillLevel_][5]);
}

void ProjectileShooter::ShootKnife()
{
	// Knife
	GameEngineRandom Random;
	Projectile* Bullet = GetLevel()->CreateActor<Projectile>(static_cast<int>(ACTOR_ORDER::PLAYER), "Bullet");
	float4 RandomPos = float4{ Random.RandomFloat(PlayerPos_.x - 25, PlayerPos_.x + 25), Random.RandomFloat(PlayerPos_.y - 25, PlayerPos_.y + 25) };
	Bullet->SetType(BulletType::KNIFE);
	Bullet->SetPosition(RandomPos);
	SetSkillStat(Bullet);
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
	Bullet->SetType(BulletType::FLAME_BLUE);
	SetSkillStat(Bullet);
	Bullet->SetDir(Vector2D::GetDirection(PlayerPos_, MonsterPos_));
	Bullet->SetPosition(PlayerPos_);

	BulletCount_ -= 1;
	isShoot_ = true;
	IntervalCount_ = InitInterval_;
}

void ProjectileShooter::ShootFire()
{
	FireShootDir_ = Vector2D::GetDirection(PlayerPos_, MonsterPos_);

	for (int i = 0; i < BulletCount_; i++)
	{
		Projectile* Bullet = GetLevel()->CreateActor<Projectile>(static_cast<int>(ACTOR_ORDER::PLAYER), "Bullet");
		Bullet->SetType(BulletType::FLAME_RED);
		SetSkillStat(Bullet);
		FireShootDir_.x *= 0.8f;
		FireShootDir_.y *= 1.2f;
		FireShootDir_.Normal2D();
		Bullet->SetDir(FireShootDir_);
		Bullet->SetPosition(PlayerPos_);
		BulletCount_ -= 1;
	}

	isShoot_ = true;
	IntervalCount_ = InitInterval_;
}
