#include "EnemyController.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineBase/GameEngineRandom.h>

#include "GameInfo.h"
#include "GameEnum.h"
#include "Enemy.h"

const int MaxEnemySpawn = 100;
const float SpawnCycle = 5.0f;

EnemyController::EnemyController() 
	: EnemyCollectorL_(nullptr)
	, EnemyCollectorR_(nullptr)
	, EnemySpawnerL_(nullptr)
	, EnemySpawnerR_(nullptr)
	, EnemiesIndex(0)
	, IsSpawnTime_(false)
{
}

EnemyController::~EnemyController() 
{
}

void EnemyController::Start()
{
	// 몬스터 스폰 주기


	// 몬스터가 충돌하면 리스폰
	EnemyCollectorL_ = CreateCollision("EnemyCollector", { 30, 700 }, { -500, 0 });
	EnemyCollectorR_ = CreateCollision("EnemyCollector", { 30, 700 }, { 500, 0 });

	// 충돌체 아닌데 그냥 표시용으로
	EnemySpawnerL_ = CreateCollision("EnemySpawner", { 100, 650 }, { -400, 0 });
	EnemySpawnerR_ = CreateCollision("EnemySpawner", { 200, 650 }, { 400, 0 });


	Enemies_.reserve(MaxEnemySpawn);

	for (int i = 0; i < MaxEnemySpawn; i++)
	{
		Enemy* Ptr = GetLevel()->CreateActor<Enemy>(static_cast<int>(ACTOR_ORDER::MONSTER), "Enemy");
		Ptr->SetPosition(float4{ 700 + static_cast<float>(i) * 50, 580 });
		Ptr->On();
		Ptr->SetDead();
		Ptr->NextLevelOff();
		Enemies_.push_back(Ptr);
	}

	SpawnCounter_.SetCount(5);
	SpawnMax_ = 7;
	SpawnNum_ = 0;
}

void EnemyController::Update()
{
	float DeltaTime = GameEngineTime::GetDeltaTime(static_cast<int>(TIME_GROUP::TIMER));
	Time_ += DeltaTime;

	SetPosition(float4{ GameInfo::GetPlayerInfo()->PlayerPos_.x, 840 });

	IsSpawnTime_ = SpawnCounter_.Start(DeltaTime);
	if (true == IsSpawnTime_)
	{
		SpawnWave();
		auto ptr = Enemies_;
		SpawnCounter_.Reset();
	}

}

void EnemyController::Render()
{

}

void EnemyController::SpawnWave()
{
	while (SpawnNum_ < SpawnMax_)
	{
		Enemy* Ptr = Enemies_[EnemiesIndex];
		if (true == Ptr->IsDead())
		{
			Ptr->On();
			Ptr->SetLive();
			
			// 생성 위치
			float4 Pos = GetSpawnPos();
			Ptr->SetPosition(Pos);

			SpawnNum_++;
			EnemiesIndex++;
		}

		if (EnemiesIndex == static_cast<int>(Enemies_.size()))
		{
			EnemiesIndex = 0;
		}
	}
}

float4 EnemyController::GetSpawnPos()
{
	float4 CurSpawnArea = EnemySpawnerR_->GetCollisionPos();
	GameEngineRandom Random;
	
	float4 SpawnPos = float4{ Random.RandomFloat(CurSpawnArea.x - 400, CurSpawnArea.x + 400),
		Random.RandomFloat(CurSpawnArea.y - 300, CurSpawnArea.y + 300) };

	return SpawnPos;
	
}
