#pragma once
#include <GameEngine/GameEngineActor.h>
#include "Counter.h"

// ¼³¸í :
class GameEngineRenderer;
class ShadeRed : public GameEngineActor
{
private:
	enum class STATE
	{
		NONE,
		CHASE,
		ALERT_CHASE,
		HIT,
		EXPLOSION,
		DIE,
	};

public:
	// constrcuter destructer
	ShadeRed();
	~ShadeRed();

	// delete Function
	ShadeRed(const ShadeRed& _Other) = delete;
	ShadeRed(ShadeRed&& _Other) noexcept = delete;
	ShadeRed& operator=(const ShadeRed& _Other) = delete;
	ShadeRed& operator=(ShadeRed&& _Other) noexcept = delete;

protected:

	void Start() override;
	void Update() override;

private:

	// FSM
	void UpdateState();
	void ChangeState(STATE _State);

	void ChaseUpdate();

	void AlertChaseUpdate();

	void HitStart();
	void HitUpdate();
	void HitEnd();

	void ExplosionStart();
	void ExplosionUpdate();
	
	void DieStart();
	void DieUpdate();
	void DieEnd();

	void HitCheck();

private:
	// FSM
	STATE State_;
	STATE ExState_;

	// ÇÊ¿äÁ¤º¸
	float4 PlayerPos_;
	float4 RedPos_;
	float4 DestDir_;

	// Counter
	//Counter DeathCounter_;
	Counter HitCounter_;
	Counter ExplodeTime_; 

	// DeltaTime
	float DeltaTime_;


	// ½ºÅÈ
	float Hp_;
	float Speed_;
	float4 KnockBackDir_;

	GameEngineRenderer* Renderer_;
	GameEngineRenderer* Ring_;
	GameEngineCollision* RedCol_;
	GameEngineCollision* BombRange_;	// Æø¹ß¹üÀ§
	GameEngineCollision* ActivateRange_;	// Æø¹ß
};

