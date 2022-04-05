#pragma once
#include <GameEngine/GameEngineActor.h>

// ���� :
// �÷��̾��� �߻�ü( Į, ����, ����, ...)
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

protected:

	void Start() override;
	void Update() override;

private:
	float4 ShootDir_;
	float4 StartPos_;
	float4 ProjPos_;
};

