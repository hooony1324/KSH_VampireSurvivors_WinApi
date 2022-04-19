#pragma once
#include <GameEngine/GameEngineActor.h>
#include <vector>
#include "Counter.h"

// ���� :
class GameEngineCollision;
class GameEngineRenderer;
class Enemy : public GameEngineActor
{
public:
	// constrcuter destructer
	Enemy();
	virtual ~Enemy();

	// delete Function
	Enemy(const Enemy& _Other) = delete;
	Enemy(Enemy&& _Other) noexcept = delete;
	Enemy& operator=(const Enemy& _Other) = delete;
	Enemy& operator=(Enemy&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;
	void Render() override;

	// �⺻ ����
	float4 PlayerPos_;
	float4 Pos_;
	float Speed_;
	int Hp_;


	// �ǰ�
	void Hit();
	GameEngineRenderer* Renderer_;
	GameEngineCollision* Col_;
	GameEngineCollision* AttackCheck_;
	float4 KnockBackDir_;


	// ���� �о��
	void BlockOther();

	GameEngineCollision* OtherBlockLeft_;
	GameEngineCollision* OtherBlockRight_;
	std::vector<GameEngineCollision*> Others_;
	std::vector<GameEngineCollision*> PlayerAttack_;


	GameEngineRenderer* Hp_BarRed_;
	float4 Hp_BarSize_;

	Counter DeathCounter_;
};

