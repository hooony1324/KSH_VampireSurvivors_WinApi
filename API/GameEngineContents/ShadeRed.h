#pragma once
#include "Enemy.h"
#include <vector>

// ���� :
class ShadeRed : public Enemy
{
public:
	// constrcuter destructer
	ShadeRed();
	~ShadeRed();

	// delete Function
	ShadeRed(const ShadeRed& _Other) = delete;
	ShadeRed(ShadeRed&& _Other) noexcept = delete;
	ShadeRed& operator=(const ShadeRed& _Other) = delete;
	ShadeRed& operator=(ShadeRed&& _Other) noexcept = delete;

private:

	void Start() override;
	void Update() override;
	void Render() override;

	// �⺻ ����
	float Speed_;
	int Hp_;


	// �ǰ�
	GameEngineRenderer* ShadeRed_;
	GameEngineCollision* ShadeRedCol_;
	GameEngineCollision* AttackCheck_;


	// ���� �о��
	void BlockOther();
	GameEngineCollision* OtherBlockUp_;
	GameEngineCollision* OtherBlockDown_;
	GameEngineCollision* OtherBlockLeft_;
	GameEngineCollision* OtherBlockRight_;
	std::vector<GameEngineCollision*> Others_;

};

