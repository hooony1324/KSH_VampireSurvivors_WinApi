#pragma once
#include <GameEngine/GameEngineActor.h>
#include <vector>
#include "Counter.h"
#include <string>

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
	void SetEnemy(int _Index);

	static int EnemyNameListIndex;
private:
	static GameEngineImage* MapColImage_;

private:
	void Start() override;
	void Update() override;
	void Render() override;

private:
	// 렌더러 세팅
	void SetRenderer();

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
	float Hp_;
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
	

	// Medusa 특수 움직임
	float UpDown_;
	Counter UpDownCounter_;
};

