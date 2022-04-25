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
	NextLevelOff();
}

void ProjectileShooter::Update()
{
	
}

void ProjectileShooter::SetShooter(SkillType _SkillType, float _WaitTime)
{
	SkillLevel_ = GameInfo::GetPlayerInfo()->SkillLevelInfo_[static_cast<int>(SkillType_)];

	//ź��		���͹�		��Ÿ��		������		�ӵ�			���ӽð� 
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

	// �Ͻ�����
	if (0.1f > GameEngineTime::GetInst()->GetTimeScale(static_cast<int>(TIME_GROUP::WEAPON)))
	{
		return;
	}


	// ��Ÿ�� �ƴϸ�
	if (0 < CoolTimeCount_)
	{
		CoolTimeCount_ -= _DeltaTime;
		return;
	}

	// �� ����(���͹� Ÿ�ӿ� �����ϸ� isShoot�� false����)
	if (true == isShoot_ || 0 < IntervalCount_)
	{
		IntervalCount_ -= _DeltaTime;
		isShoot_ = false;
		return;
	}

	// �� ���� �ƴϸ�, ���͹��� ��������
	
	// �Ѿ��� ������, ������ �Ѿ˼�, ��Ÿ��, ... ����
	if (BulletCount_ == 0)
	{
		BulletCount_ = InitBulletCount_;
		CoolTimeCount_ = InitCoolTime_;
		isShoot_ = false;
		IntervalCount_ = 0;
		return;
	}

	// �Ѿ� ������ ���
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
	//ź��		���͹�		��Ÿ��		������		�ӵ�			���ӽð� 
	SkillLevel_ = GameInfo::GetPlayerInfo()->SkillLevelInfo_[static_cast<int>(SkillType_)];
	InitBulletCount_ = static_cast<int>(STAT_SHOOTER[static_cast<int>(SkillType_)][SkillLevel_][0]);
	InitInterval_ = STAT_SHOOTER[static_cast<int>(SkillType_)][SkillLevel_][1];
	InitCoolTime_ = STAT_SHOOTER[static_cast<int>(SkillType_)][SkillLevel_][2];

	_Bullet->SetDamage(STAT_SHOOTER[static_cast<int>(SkillType_)][SkillLevel_][3]);
	_Bullet->SetSpeed(STAT_SHOOTER[static_cast<int>(SkillType_)][SkillLevel_][4]);
	_Bullet->SetDuration(STAT_SHOOTER[static_cast<int>(SkillType_)][SkillLevel_][5]);
}

void ProjectileShooter::ShootKnife()
{
	// Knife
	Projectile* Bullet = GetLevel()->CreateActor<Projectile>(static_cast<int>(ACTOR_ORDER::PLAYER), "Bullet");
	Bullet->SetType(BulletType::KNIFE);
	SetSkillStat(Bullet);
	float4 RandomPos = float4{ static_cast<float>(Random.RandomInt(PlayerPos_.ix() - 25, PlayerPos_.ix() + 25)), static_cast<float>(Random.RandomInt(PlayerPos_.iy() - 25, PlayerPos_.iy() + 25))};
	Bullet->SetPosition(RandomPos);
	Bullet->SetDir(PlayerMoveDir_);


	BulletCount_ -= 1;
	isShoot_ = true;
	IntervalCount_ = InitInterval_;
}

void ProjectileShooter::ShootMagic()
{
	// MagicWand
	// �Ѿ� ��� isShoot = true
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
