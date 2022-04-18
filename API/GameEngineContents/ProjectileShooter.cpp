#include "ProjectileShooter.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>

#include "ObjectEnum.h"
#include "Vector2D.h"

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
}

void ProjectileShooter::Update()
{

}

void ProjectileShooter::InitShooter(BulletType _BT, int _BulletCount, float _Interval, float _CoolTime, float _WaitTime)
{
	InitBulletCount_ = _BulletCount;
	InitInterval_ = _Interval;
	InitCoolTime_ = _CoolTime;
	BT_ = _BT;
	isShoot_ = false;
	
	CoolTimeCount_ = _WaitTime;
	BulletCount_ = InitBulletCount_;
	IntervalCount_ = InitInterval_;
}

void ProjectileShooter::Shooting(float _DeltaTime, float4 _PlayerPos, float4 _MonsterPos)
{
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
	
	// �Ѿ��� ������
	if (BulletCount_ == 0)
	{
		BulletCount_ = InitBulletCount_;
		CoolTimeCount_ = InitCoolTime_;
		isShoot_ = false;
		IntervalCount_ = 0;
		return;
	}

	// MagicWand
	// �Ѿ� ��� isShoot = true
	Projectile* Bullet = GetLevel()->CreateActor<Projectile>(static_cast<int>(ACTOR_ORDER::PLAYER), "Bullet");
	Bullet->SetType(BT_);
	Bullet->SetPosition(_PlayerPos);
	Bullet->SetDir(Vector2D::GetDirection(_PlayerPos, _MonsterPos));
	BulletCount_ -= 1;
	isShoot_ = true;
	IntervalCount_ = InitInterval_;

	return;
}