#pragma once
#include "Enemy.h"
#include <vector>
// ���� :
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

	void TestMud() {}

protected:

	void Start() override;
	void Update() override;
	void Render() override;

private:
	// �⺻ ����
	float Speed_;
	int Hp_;




	// �ǰ�
	GameEngineRenderer* Mud_;
	GameEngineCollision* MudCol_;
	GameEngineCollision* AttackCheck_;


	// ���� �о��
	void BlockOther();
	GameEngineCollision* OtherBlockUp_;
	GameEngineCollision* OtherBlockDown_;
	GameEngineCollision* OtherBlockLeft_;
	GameEngineCollision* OtherBlockRight_;
	std::vector<GameEngineCollision*> Others_;

};

