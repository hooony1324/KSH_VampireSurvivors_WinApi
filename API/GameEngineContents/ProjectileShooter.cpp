#include "ProjectileShooter.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include "ObjectOrder.h"

#include "Vector2D.h"

ProjectileShooter::ProjectileShooter()
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

void ProjectileShooter::InitShooter(BulletType _BT, int _Count, float _Interval, float _CoolTime, float _WaitTime)
{
	InitBulletCount_ = _Count;
	InitInterval_ = _Interval;
	InitCoolTime_ = _CoolTime;
	BT_ = _BT;
	isShoot_ = false;

	
	CoolTimeCount_ = _WaitTime;
	BulletCount_ = InitBulletCount_;
	IntervalCount_ = InitInterval_;
}

Projectile* ProjectileShooter::Shooting(float _DeltaTime, float4 _PlayerPos, float4 _MonsterPos)
{
	// �÷��̾�� ������ ��ġ�� ����
	SetPosition(_PlayerPos);

	// ��Ÿ�� �ƴϸ�
	if (0 < CoolTimeCount_)
	{
		CoolTimeCount_ -= _DeltaTime;
		return nullptr;
	}

	// �� ����(���͹� Ÿ�ӿ� �����ϸ� isShoot�� false����)
	if (true == isShoot_ || 0 < IntervalCount_)
	{
		IntervalCount_ -= _DeltaTime;
		isShoot_ = false;
		return nullptr;
	}

	// �� ���� �ƴϸ�, ���͹��� ��������
	
	// �Ѿ��� ������
	if (BulletCount_ == 0)
	{
		BulletCount_ = InitBulletCount_;
		CoolTimeCount_ = InitCoolTime_;
		isShoot_ = false;
		IntervalCount_ = 0;
		return nullptr;
	}

	// �Ѿ� ��� isShoot = true
	Projectile* Bullet = GetLevel()->CreateActor<Projectile>(static_cast<int>(ACTOR_ORDER::PLAYER), "Bullet");
	Bullet->SetType(BT_);
	Bullet->SetPosition(_PlayerPos);
	Bullet->SetDir(Vector2D::GetDirection(_PlayerPos, _MonsterPos));
	Bullet->Death(3);				// �ɷ�ġ�� ���� �޶�������
	BulletCount_ -= 1;
	isShoot_ = true;
	IntervalCount_ = InitInterval_;

	return Bullet;
}