#pragma once
#include <GameEngine/GameEngineActor.h>
#include <vector>
#include "Counter.h"

// 설명 :
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

	static int LiveEnemyNum;

protected:

	void Start() override;
	void Update() override;
	void Render() override;

private:

	void SpawnWave();
	void SpawnBoss(bool _BossCounter);
	float4 GetSpawnPos();

private:
	float Time_;

	std::vector<Enemy*> Enemies_;
	int EnemiesIndex;
	int SpawnMax_;	// 최대 스폰
	int SpawnNum_;	// 스폰 수

	Counter SpawnCounter_;
	bool IsSpawnTime_;
	float4 SpawnPosR_;

private:
	
	// SpawnBoss관련
	Counter BossCounter_;
	int BossIndex_;
	// ShadeRed -> 1
	// XLMummy -> 2
	// { 1, 0, 0, 0, 2, ...}
	// 1칸-> 1분
};

