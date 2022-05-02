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
	float Time_;
	void WaveIndexUpdate();
	void SpawnWave();
	void SpawnBoss(bool _BossCounterEnd);
	float4 GetSpawnPos();
	void ChangeSpawnPosBase();

// SpawnEnemy관련
private:
	std::vector<Enemy*> Enemies_;
	int EnemiesIndex;
	int SpawnMax_;	// 1회 최대 스폰
	int SpawnNum_;	// 스폰 수

	Counter SpawnCounter_;
	bool IsSpawnTime_;
	int SpawnLeftRight_;
	float4 SpawnPosBase_;

// SpawnBoss관련
private:
	void SpawnReaperButton();
	Counter BossCounter_;
	int BossIndex_;

// SpawnShadeRed
private:
	Counter ShadeRedCounter_;
	void SpawnShadeRed(bool _CounterEnd);


// TimeCheck관련
private:
	int WaveIndex_;
};

