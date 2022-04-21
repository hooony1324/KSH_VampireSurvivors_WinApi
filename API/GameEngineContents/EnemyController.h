#pragma once
#include <GameEngine/GameEngineActor.h>
#include <vector>
#include "Counter.h"

// ���� :
class GameEngineActor;
class EnemyController : public GameEngineActor
{
public:
	// constrcuter destructer
	EnemyController();
	~EnemyController();

	// delete Function
	EnemyController(const EnemyController& _Other) = delete;
	EnemyController(EnemyController&& _Other) noexcept = delete;
	EnemyController& operator=(const EnemyController& _Other) = delete;
	EnemyController& operator=(EnemyController&& _Other) noexcept = delete;

protected:

	void Start() override;
	void Update() override;
	void Render() override;

private:

	void Spawn();

private:

	GameEngineCollision* EnemyCollectorL_;
	GameEngineCollision* EnemyCollectorR_;

	GameEngineCollision* EnemySpawnerL_;
	GameEngineCollision* EnemySpawnerR_;

	std::vector<GameEngineActor*> Enemies_;

	Counter SpawnCounter_;
	bool IsSpawn_;
};

