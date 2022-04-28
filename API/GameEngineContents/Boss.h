#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineMath.h>
#include <string>
#include "Counter.h"

enum class BOSSTYPE
{
	SHADERED,
	XLMUMMY,
	MAX
};


// ¼³¸í :
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
		RED_ALARMCHASE,
		RED_DIE
	};

	static int BossIndex_;

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

	// ½ÃÇÑÆøÅº ¸÷ + ÆøÆÄÁ×À½
	void RedAlarmChaseStart();
	void RedAlarmChaseUpdate();
	void RedDieStart();
	void RedDieUpdate();

	// ½ºÅÈ
	void SetStat();

	// ÄÝ¸®Àü¸Ê Ã¼Å©
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

	// ½ºÅÈ
	float Hp_;
	float Speed_;

	// ±âÅ¸
	float4 PlayerPos_;
	float4 BossPos_;

	GameEngineImage* MapColImage_;

	// ¹Ð¾î³»±â
	std::vector<GameEngineCollision*> Enemies_;

	// ÇÇ°Ý
	GameEngineCollision* BossCol_;
	std::vector<GameEngineCollision*> PlayerAttack_;
	float HitDamage_;
	float4 KnockBackDir_;
	float KnockBackRatio_;

	// Æ¯¼ö : ShadeRed
	GameEngineCollision* BombRange_;	// Æø¹ß¹üÀ§
	GameEngineCollision* ActivateRange_;	// Æø¹ß
	Counter BombTime_;
	

};

