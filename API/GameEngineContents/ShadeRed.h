#pragma once
#include "Enemy.h"
#include <vector>
#include "Counter.h"

// ���� :
class GameEngineCollision;
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

	void Hit();

	// �⺻ ����
	float Speed_;
	float Hp_;
	GameEngineRenderer* Hp_BarRed_;
	float4 Hp_BarSize_;

	// �ǰ�
	GameEngineRenderer* ShadeRed_;
	GameEngineCollision* ShadeRedCol_;


	// ���� �о��
	void BlockOther();
	GameEngineCollision* OtherBlockUp_;
	GameEngineCollision* OtherBlockDown_;
	GameEngineCollision* OtherBlockLeft_;
	GameEngineCollision* OtherBlockRight_;
	std::vector<GameEngineCollision*> Others_;

	Counter Counter1_;

};

