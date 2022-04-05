#pragma once
#include "Enemy.h"
#include <vector>
// Ό³Έν :
class GameEngineCollision;
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

	void PushOther();

protected:

	void Start() override;
	void Update() override;
	void Render() override;

private:

	GameEngineRenderer* Mud_;
	GameEngineCollision* MudCol_;

	GameEngineCollision* OtherBlockUp_;
	GameEngineCollision* OtherBlockDown_;
	GameEngineCollision* OtherBlockLeft_;
	GameEngineCollision* OtherBlockRight_;

	std::vector<GameEngineCollision*> Others_;


	float Speed_;
};

