#pragma once
#include <GameEngine/GameEngineActor.h>
#include "Projectile.h"
#include "GameEnum.h"

// ���� :

class ProjectileShooter : public GameEngineActor
{
public:
	// constrcuter destructer
	ProjectileShooter();
	~ProjectileShooter();

	// delete Function
	ProjectileShooter(const ProjectileShooter& _Other) = delete;
	ProjectileShooter(ProjectileShooter&& _Other) noexcept = delete;
	ProjectileShooter& operator=(const ProjectileShooter& _Other) = delete;
	ProjectileShooter& operator=(ProjectileShooter&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;

public:

	void SetShooter(SkillType _SkillType , BulletType _BT, int _BulletCount, float _Interval, float _CoolTime, float _WaitTime = 0);	// �߻�ü, �߻� Ƚ��, ���͹�, ��Ÿ��
	void Shooting(float _DeltaTime, float4 _PlayerPos, float4 _MonsterPos, float4 _PlayerMoveDir = float4::ZERO);								// �Ѿ��ϳ� �߻��ϸ� Level�� �Ѿ������� �Ѱ���ߵ� 

	inline void StopShooting()
	{
		ShootAble_ = false;
	}
	inline void StartShooting()
	{
		ShootAble_ = true;
	}

protected:

private:
	void ShootKnife();
	void ShootMagic();
	void ShootFire();

	bool ShootAble_;

	Projectile* Projectile_;
	BulletType BT_;
	SkillType SkillType_;

	// �ʱ����
	int InitBulletCount_;
	float InitInterval_;
	float InitCoolTime_;

	// ���� ����
	int BulletCount_;
	float IntervalCount_;
	float CoolTimeCount_;
	bool isShoot_;

	float4 PlayerMoveDir_;
	float4 PlayerPos_;
	float4 MonsterPos_;
	float4 FireShootDir_;

};

