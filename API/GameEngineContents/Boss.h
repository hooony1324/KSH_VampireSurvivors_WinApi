#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineMath.h>
#include <string>
#include "Counter.h"
#include <vector>

enum class BOSSTYPE
{
	XLMUMMY,
	XLRREAPER,
	MAX
};


// 설명 :
class GameEngineCollision;
class GameEngineRenderer;
class GameEngineImage;
class Boss : public GameEngineActor
{
public:
	enum class BOSS_STATE
	{
		CHASE,
		HIT,
		DIE,
	};

	static int BossIndex_;
	static bool IsReaperSpawn_;

public:
	// constrcuter destructer
	Boss();
	~Boss();

	// delete Function
	Boss(const Boss& _Other) = delete;
	Boss(Boss&& _Other) noexcept = delete;
	Boss& operator=(const Boss& _Other) = delete;
	Boss& operator=(Boss&& _Other) noexcept = delete;



protected:
	void Start() override;
	void Update() override;
	void Render() override;

private:
	void SetRenderer(BOSSTYPE _BossType);
	BOSSTYPE BossType_;

	// FSM
	void UpdateState();
	void ChangeState(BOSS_STATE _State);

	void ChaseUpdate();

	void HitStart();
	void HitUpdate();
	void HitEnd();

	void DieStart();
	void DieUpdate();
	void DieEnd();

	// 스탯
	void SetStat();

	// 콜리전맵 체크
	float MapColCheck(float _Speed, float4 _DestDir);

	void BlockEnemies();
	void HitCheck();

private:
	std::string BossName_;

	// FSM
	BOSS_STATE State_;

	// Counter
	Counter HitCounter_;
	Counter DeathCounter_;

	// DeltaTime
	float DeltaTime_;

	GameEngineRenderer* Renderer_;

	// 스탯
	float Hp_;
	float Speed_;
	float4 DestDir_;

	// 기타
	float4 PlayerPos_;
	float4 BossPos_;

	GameEngineImage* MapColImage_;

	// 밀어내기
	std::vector<GameEngineCollision*> Enemies_;

	// 피격
	GameEngineCollision* BossCol_;
	std::vector<GameEngineCollision*> PlayerAttack_;
	float HitDamage_;
	float4 KnockBackDir_;
	float KnockBackDis_;
	float KnockBackRatio_;

};

