#pragma once
#include <GameEngine/GameEngineActor.h>
#include <vector>
#include "Counter.h"
#include <string>

// ���� :
class GameEngineCollision;
class GameEngineRenderer;
class GameEngineImage;
class Enemy : public GameEngineActor
{
private:
	enum class STATE
	{
		DEAD,
		DIE,
		CHASE,
		HIT,
	};

	STATE State_;

	void UpdateState();
	void ChangeState(STATE _State);

	void DeadStart();
	void DeadUpdate();

	void DieStart();
	void DieUpdate();

	void ChaseUpdate();
	
	void HitStart();
	void HitUpdate();
	void HitEnd();

	void HitCheck();
	float HitDamage_;

public:
	// constrcuter destructer
	Enemy();
	virtual ~Enemy();

	// delete Function
	Enemy(const Enemy& _Other) = delete;
	Enemy(Enemy&& _Other) noexcept = delete;
	Enemy& operator=(const Enemy& _Other) = delete;
	Enemy& operator=(Enemy&& _Other) noexcept = delete;

	inline bool IsDead()
	{
		return Dead_;
	}

	void SetDead();

	void SetLive();

	// �ܺο��� EnemySet ����
	void SetEnemy(int _Index);

	static int EnemyNameListIndex;
private:
	static GameEngineImage* MapColImage_;

private:
	void Start() override;
	void Update() override;

private:
	// ������ ����
	void SetRenderer();

	// �ݸ��� ��
	float MapColCheck(float _DestDir);

	// ���� �о��
	void BlockOther();

	void UpdateHeadDir();

private:
	float DeltaTime_;

	// �⺻����
	std::string EnemyName_;
	GameEngineRenderer* Renderer_;
	float Speed_;
	float Hp_;
	bool Dead_;
	int DeadCount_;
	
	float4 PlayerPos_;
	float4 Pos_;
	float4 DestDir_;

	// �ǰ�
	std::vector<GameEngineCollision*> PlayerAttack_;
	GameEngineCollision* Col_;
	float4 KnockBackDir_;
	float KnockBackDis_;
	bool Hitable_;

	// �о��
	GameEngineCollision* OtherBlockLeft_;
	GameEngineCollision* OtherBlockRight_;
	std::vector<GameEngineCollision*> Others_;

	// Medusa Ư�� ������
	float UpDown_;

	Counter HitCounter_;
	Counter DeathCounter_;
	Counter UpDownCounter_;
};

