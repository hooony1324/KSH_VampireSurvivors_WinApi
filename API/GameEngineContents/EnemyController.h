#pragma once
#include <GameEngine/GameEngineActor.h>
#include <vector>
#include "Counter.h"

// Ό³Έν :
class GameEngineActor;
class Enemy;
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

	void SpawnWave();
	float4 GetSpawnPos();

private:
	float Time_;

	GameEngineCollision* EnemyCollectorL_;
	GameEngineCollision* EnemyCollectorR_;

	GameEngineCollision* EnemySpawnerL_;
	GameEngineCollision* EnemySpawnerR_;

	std::vector<Enemy*> Enemies_;
	int EnemiesIndex;
	int SpawnMax_;
	int SpawnNum_;


	Counter SpawnCounter_;
	bool IsSpawnTime_;

};

