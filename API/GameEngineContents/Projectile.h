#pragma once
#include <GameEngine/GameEngineActor.h>
#include <vector>
#include <GameEngineBase/GameEngineSound.h>
#include "PlayerAttack.h"

enum class ProjectileType
{
	NONE,
	KNIFE,
	FLAME_BLUE,
	FLAME_RED,
	DIAMOND,
};


// 플레이어의 발사체( 칼, 매직, 도끼, ...)
class GameEngineRenderer;
class GameEngineCollision;
class GameEngineImage;
class Projectile : public PlayerAttack
{	
public:

	// constrcuter destructer
	Projectile();
	~Projectile();

	// delete Function
	Projectile(const Projectile& _Other) = delete;
	Projectile(Projectile&& _Other) noexcept = delete;
	Projectile& operator=(const Projectile& _Other) = delete;
	Projectile& operator=(Projectile&& _Other) noexcept = delete;

	void SetType(ProjectileType _BT);

	void SetDir(float4 _Direction);

	float GetDamage() override
	{
		return Damage_;
	}

	void SetDamage(float _Damage) override
	{
		Damage_ = _Damage;
	}

	void SetDuration(float _Duration)
	{
		Duration_ = _Duration;
	}

	void SetSpeed(float _Speed)
	{
		Speed_ = _Speed;
	}

	bool IsBullet() override
	{
		return IsBullet_;
	}

protected:

	void Start() override;
	void Update() override;
	void Render() override;


private:

	void DiamondUpdate();

private:
	ProjectileType Type_;

	bool IsBullet_;
	float Damage_;
	float Speed_;
	float Duration_;// 총알 지속시간

	GameEngineRenderer* ProjImage_;
	GameEngineCollision* ProjCol_;

	float4 ShootDir_;
	
	GameEngineImage* MapColImage_;



};

