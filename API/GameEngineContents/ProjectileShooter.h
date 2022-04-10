#pragma once
#include <GameEngine/GameEngineActor.h>
#include "Projectile.h"

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

	// 시간을 계속 받아야 한다

	// 무한 반복한다

	// Projectile의 타입을 세팅(공격력, 스피드, 이미지, ...)


	void InitShooter(BulletType _BT, int _Count, float _Interval, float _CoolTime, float _WaitTime = 0);	// 발사체, 발사 횟수, 인터벌, 쿨타임
	void Shooting(float _DeltaTime, float4 _PlayerPos, float4 _MonsterPos);								// 총알하나 발사하면 Level에 총알포인터 넘겨줘야됨 

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

	// 초기상태
	int InitBulletCount_;
	float InitInterval_;
	float InitCoolTime_;

	// 현재 상태
	int BulletCount_;
	float IntervalCount_;
	float CoolTimeCount_;
	bool isShoot_;

};

