#pragma once
#include <GameEngine/GameEngineActor.h>
#include <vector>

enum class BulletType
{
	SWORD,
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

	void SetType(BulletType _BT);

	void SetDir(float4 _Direction)
	{
		ShootDir_ = _Direction;
	}

	GameEngineRenderer* GetProjImage()
	{
		return ProjImage_;
	}

protected:

	void Start() override;
	void Update() override;
	void Render() override;

private:

	GameEngineRenderer* ProjImage_;
	GameEngineCollision* ProjCol_;

	float4 ShootDir_;
	float4 ProjVec_;
	int Damage_;
};

