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

{
}

ProjectileShooter::~ProjectileShooter() 
{
}

void ProjectileShooter::Start()
{
	NextLevelOff();
}

void ProjectileShooter::Update()
{
	UpdateSkillStat();

}

void ProjectileShooter::SetShooter(SkillType _SkillType, float _WaitTime)
{
	SkillLevel_ = GameInfo::GetPlayerInfo()->SkillLevelInfo_[static_cast<int>(_SkillType)];

	//탄수		인터벌		쿨타임		데미지		속도			지속시간 
	SkillType_ = _SkillType;
	InitBulletCount_ = static_cast<int>(STAT_SHOOTER[static_cast<int>(SkillType_)][SkillLevel_][0]);
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
	
	// 총알이 없으면, 설정된 총알수, 쿨타임, ... 리셋
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

void ProjectileShooter::UpdateSkillStat()
{
	SkillLevel_ = GameInfo::GetPlayerInfo()->SkillLevelInfo_[static_cast<int>(SkillType_)];
	InitBulletCount_ = static_cast<int>(STAT_SHOOTER[static_cast<int>(SkillType_)][SkillLevel_][0]);
	InitInterval_ = STAT_SHOOTER[static_cast<int>(SkillType_)][SkillLevel_][1];
	InitCoolTime_ = STAT_SHOOTER[static_cast<int>(SkillType_)][SkillLevel_][2];
}

void ProjectileShooter::SetBulletStat(Projectile* _Bullet)
{
	_Bullet->SetDamage(STAT_SHOOTER[static_cast<int>(SkillType_)][SkillLevel_][3]);
	_Bullet->SetSpeed(STAT_SHOOTER[static_cast<int>(SkillType_)][SkillLevel_][4]);
	_Bullet->SetDuration(STAT_SHOOTER[static_cast<int>(SkillType_)][SkillLevel_][5]);
}

void ProjectileShooter::ShootKnife()
{
	Projectile* Bullet = GetLevel()->CreateActor<Projectile>(static_cast<int>(ACTOR_ORDER::PLAYER), "Bullet");
	Bullet->SetType(BulletType::KNIFE);
	SetBulletStat(Bullet);
	float4 RandomPos = float4{ static_cast<float>(Random.RandomInt(PlayerPos_.ix() - 25, PlayerPos_.ix() + 25)), static_cast<float>(Random.RandomInt(PlayerPos_.iy() - 25, PlayerPos_.iy() + 25))};
	Bullet->SetPosition(RandomPos);
	Bullet->SetDir(PlayerMoveDir_);


	BulletCount_ -= 1;
	isShoot_ = true;
	IntervalCount_ = InitInterval_;
}

void ProjectileShooter::ShootMagic()
{
	Projectile* Bullet = GetLevel()->CreateActor<Projectile>(static_cast<int>(ACTOR_ORDER::PLAYER), "Bullet");
	Bullet->SetType(BulletType::FLAME_BLUE);
	SetBulletStat(Bullet);
	Bullet->SetPosition(PlayerPos_);
	Bullet->SetDir(Vector2D::GetDirection(PlayerPos_, MonsterPos_));

	BulletCount_ -= 1;
	isShoot_ = true;
	IntervalCount_ = InitInterval_;
}

void ProjectileShooter::ShootFire()
{
	// 0에 가까운 값이 나올수록 각도가 벌어지지 않는다
	float4 FireShootDir = Vector2D::GetDirection(PlayerPos_, MonsterPos_);
	
	// 한번에 쏜다
	for (int i = 0; i < BulletCount_; i++)
	{
		Projectile* Bullet = GetLevel()->CreateActor<Projectile>(static_cast<int>(ACTOR_ORDER::PLAYER), "Bullet");
		Bullet->SetType(BulletType::FLAME_RED);
		SetBulletStat(Bullet);
		float4 RotateDir;
		RotateDir = float4::VectorRotationToDegreeZ(FireShootDir, 15 * static_cast<float>(i));
		RotateDir.Normal2D();
		Bullet->SetDir(RotateDir);
		Bullet->SetPosition(PlayerPos_);
	}
	
	BulletCount_ = 0;

	isShoot_ = true;
	IntervalCount_ = InitInterval_;
}
