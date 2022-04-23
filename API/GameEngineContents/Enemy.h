#pragma once
#include <GameEngine/GameEngineActor.h>
#include <vector>
#include "Counter.h"

// 설명 :
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

	// 외부에서 EnemySet 관련
	void SetNextEnemy();

private:
	static GameEngineImage* MapColImage_;

private:
	void Start() override;
	void Update() override;
	void Render() override;

private:
	// 콜리전 맵
	float MapColCheck(float _DestDir);
	// 피격
	void Hit();
	// 서로 밀어내기
	void BlockOther();
	// 죽음
	void EnemyDead();

	void EnemyMove();

	void UpdateHeadDir();

private:
	float DeltaTime_;

	// 기본정보
	std::string EnemyName_;
	GameEngineRenderer* Renderer_;
	float Speed_;
	int Hp_;
	bool Dead_;
	
	float4 PlayerPos_;
	float4 Pos_;
	float4 DestDir_;

	// 피격
	std::vector<GameEngineCollision*> PlayerAttack_;
	GameEngineCollision* Col_;
	float4 KnockBackDir_;

	// 밀어내기
	GameEngineCollision* OtherBlockLeft_;
	GameEngineCollision* OtherBlockRight_;
	std::vector<GameEngineCollision*> Others_;

	Counter DeathCounter_;

	// 외부에서 EnemySet 관련
	bool SetSignalOn;
};

