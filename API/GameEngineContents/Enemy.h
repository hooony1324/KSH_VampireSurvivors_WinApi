#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
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

	virtual void KillEnemy() = 0;

private:
	void Update() override;

};

