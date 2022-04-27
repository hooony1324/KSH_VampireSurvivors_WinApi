#pragma once
#include <GameEngine/GameEngineActor.h>
#include "Projectile.h"
#include "GameEnum.h"

// 설명 :

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

	void SetShooter(SkillType _SkillType, float _WaitTime = 0.0f);	// 발사체, 발사 횟수, 인터벌, 쿨타임
	void Shooting(float _DeltaTime, float4 _PlayerPos, float4 _MonsterPos, float4 _PlayerMoveDir = float4::ZERO);								// 총알하나 발사하면 Level에 총알포인터 넘겨줘야됨 

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

	// 초기상태
	int InitBulletCount_;
	float InitInterval_;
	float InitCoolTime_;

	// 현재 상태
	int BulletCount_;
	float IntervalCount_;
	float CoolTimeCount_;
	bool isShoot_;

	float4 PlayerMoveDir_;
	float4 PlayerPos_;
	float4 MonsterPos_;

	int SkillLevel_;
	
};

