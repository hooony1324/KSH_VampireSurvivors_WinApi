#pragma once
#include <GameEngine/GameEngineActor.h>

// 설명 :
// 플레이어의 발사체( 칼, 매직, 도끼, ...)
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

	float4 GetStartPos()
	{
		return StartPos_;
	}

	// InfiniteMap에 의해 플레이어 이동 시 Projectie의 위치도 변하도록
	void AdjustStartPos(float4 _Pos)
	{
		StartPos_ += _Pos;
	}

protected:

	void Start() override;
	void Update() override;

private:
	float4 ShootDir_;
	float4 ProjVec_;
	float4 StartPos_;
};

