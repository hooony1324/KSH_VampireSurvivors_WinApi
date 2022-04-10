#pragma once
#include <GameEngine/GameEngineActor.h>
#include "Projectile.h"

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

	// �ð��� ��� �޾ƾ� �Ѵ�

	// ���� �ݺ��Ѵ�

	// Projectile�� Ÿ���� ����(���ݷ�, ���ǵ�, �̹���, ...)


	void InitShooter(BulletType _BT, int _Count, float _Interval, float _CoolTime, float _WaitTime = 0);	// �߻�ü, �߻� Ƚ��, ���͹�, ��Ÿ��
	void Shooting(float _DeltaTime, float4 _PlayerPos, float4 _MonsterPos);								// �Ѿ��ϳ� �߻��ϸ� Level�� �Ѿ������� �Ѱ���ߵ� 

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
	bool ShootAble_;

	Projectile* Projectile_;
	BulletType BT_;

	// �ʱ����
	int InitBulletCount_;
	float InitInterval_;
	float InitCoolTime_;

	// ���� ����
	int BulletCount_;
	float IntervalCount_;
	float CoolTimeCount_;
	bool isShoot_;

};

