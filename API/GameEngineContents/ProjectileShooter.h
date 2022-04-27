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

	void SetShooter(SkillType _SkillType, float _WaitTime = 0.0f);	// �߻�ü, �߻� Ƚ��, ���͹�, ��Ÿ��
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
	void UpdateSkillStat();
	void SetBulletStat(Projectile* _Bullet);

	void ShootKnife();
	void ShootMagic();
	void ShootFire();

	bool ShootAble_;

	Projectile* Projectile_;
	ProjectileType BT_;
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

	int SkillLevel_;
	
};

