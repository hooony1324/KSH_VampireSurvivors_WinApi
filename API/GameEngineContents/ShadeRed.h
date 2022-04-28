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
		CHASE,
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

private:
	// FSM
	STATE State_;

	// Counter
	//Counter HitCounter_;
	//Counter DeathCounter_;
	Counter ExplodeTime_; 

	// DeltaTime
	float DeltaTime_;


	// ½ºÅÈ
	float Hp_;
	float Speed_;

	GameEngineRenderer* Renderer_;
	GameEngineCollision* BombRange_;	// Æø¹ß¹üÀ§
	GameEngineCollision* ActivateRange_;	// Æø¹ß
};

