#pragma once
#include "Enemy.h"

// Ό³Έν :
class Mud : public Enemy
{
public:
	// constrcuter destructer
	Mud();
	~Mud();

	// delete Function
	Mud(const Mud& _Other) = delete;
	Mud(Mud&& _Other) noexcept = delete;
	Mud& operator=(const Mud& _Other) = delete;
	Mud& operator=(Mud&& _Other) noexcept = delete;

	void KillEnemy() override;

protected:

	void Start() override;
	void Render() override;

private:

	GameEngineRenderer* Mud_;
	GameEngineCollision* MudCol_;
};

