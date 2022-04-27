#pragma once
#include <GameEngine/GameEngineActor.h>
#include <vector>
#include <GameEngineBase/GameEngineSound.h>

enum class ProjectileType
{
	KNIFE,
	FLAME_BLUE,
	FLAME_RED
};


// 플레이어의 발사체( 칼, 매직, 도끼, ...)
class GameEngineRenderer;
class GameEngineCollision;
class Projectile : public GameEngineActor
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

	GameEngineRenderer* GetProjImage()
	{
		return ProjImage_;
	}


	float GetDamage()
	{
		return Damage_;
	}

	void SetDamage(float _Damage)
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

	bool IsBullet()
	{
		return IsBullet_;
	}

protected:

	void Start() override;
	void Update() override;
	void Render() override;

private:
	bool IsBullet_;

	GameEngineRenderer* ProjImage_;
	GameEngineCollision* ProjCol_;

	float4 ShootDir_;
	
	
	float Damage_;
	float Speed_;
	float Duration_;// 총알 지속시간



};

