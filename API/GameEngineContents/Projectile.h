#pragma once
#include <GameEngine/GameEngineActor.h>

// ���� :
// �÷��̾��� �߻�ü( Į, ����, ����, ...)
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

	// InfiniteMap�� ���� �÷��̾� �̵� �� Projectie�� ��ġ�� ���ϵ���
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

