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

	inline void SetDead()
	{
		Dead_ = true;
	}

	inline void SetLive()
	{
		Dead_ = false;
	}

	// �ܺο��� EnemySet ����
	void SetEnemy(int _Index);

	static int EnemyNameListIndex;
private:
	static GameEngineImage* MapColImage_;

private:
	void Start() override;
	void Update() override;
	void Render() override;

private:
	// ������ ����
	void SetRenderer();

	// �ݸ��� ��
	float MapColCheck(float _DestDir);
	// �ǰ�
	void Hit();
	// ���� �о��
	void BlockOther();
	// ����
	void EnemyDead();

	void EnemyMove();

	void UpdateHeadDir();

private:
	float DeltaTime_;

	// �⺻����
	std::string EnemyName_;
	GameEngineRenderer* Renderer_;
	float Speed_;
	float Hp_;
	bool Dead_;
	
	float4 PlayerPos_;
	float4 Pos_;
	float4 DestDir_;

	// �ǰ�
	std::vector<GameEngineCollision*> PlayerAttack_;
	GameEngineCollision* Col_;
	float4 KnockBackDir_;

	// �о��
	GameEngineCollision* OtherBlockLeft_;
	GameEngineCollision* OtherBlockRight_;
	std::vector<GameEngineCollision*> Others_;

	Counter DeathCounter_;

	// �ܺο��� EnemySet ����
	

	// Medusa Ư�� ������
	float UpDown_;
	Counter UpDownCounter_;
};

