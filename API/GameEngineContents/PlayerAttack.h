#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class PlayerAttack : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayerAttack();
	virtual ~PlayerAttack();

	// delete Function
	PlayerAttack(const PlayerAttack& _Other) = delete;
	PlayerAttack(PlayerAttack&& _Other) noexcept = delete;
	PlayerAttack& operator=(const PlayerAttack& _Other) = delete;
	PlayerAttack& operator=(PlayerAttack&& _Other) noexcept = delete;

	virtual float GetDamage() = 0;

	virtual void SetDamage(float _Damage) = 0;

	virtual bool IsBullet() = 0;

protected:

private:


};

