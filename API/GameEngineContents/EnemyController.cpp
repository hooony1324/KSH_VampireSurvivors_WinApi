#include "EnemyController.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineLevel.h>

#include "GameInfo.h"
#include "GameEnum.h"
#include "Enemy.h"

const int EnemyNumInScene = 4;
const float SpawnCycle = 120.0f;

EnemyController::EnemyController() 
	: EnemyCollectorL_(nullptr)
	, EnemyCollectorR_(nullptr)
	, EnemySpawnerL_(nullptr)
	, EnemySpawnerR_(nullptr)
{
}

EnemyController::~EnemyController() 
{
}

void EnemyController::Start()
{
	// ���� ���� �ֱ� : 2��
	SpawnCounter_.SetCount(SpawnCycle);

	// ���Ͱ� �浹�ϸ� ������
	EnemyCollectorL_ = CreateCollision("EnemyCollector", { 30, 700 }, { -500, 0 });
	EnemyCollectorR_ = CreateCollision("EnemyCollector", { 30, 700 }, { 500, 0 });

	// �浹ü �ƴѵ� �׳� ǥ�ÿ�����
	EnemySpawnerL_ = CreateCollision("EnemySpawner", { 30, 650 }, { -400, 0 });
	EnemySpawnerR_ = CreateCollision("EnemySpawner", { 30, 650 }, { 400, 0 });


	Enemies_.reserve(EnemyNumInScene);
	for (int i = 0; i < EnemyNumInScene; i++)
	{
		GameEngineActor* Ptr = GetLevel()->CreateActor<Enemy>(static_cast<int>(ACTOR_ORDER::MONSTER), "Enemy");
		Ptr->SetPosition(float4{ static_cast<float>(i) * 50, 40 });
		Ptr->On();
		Ptr->NextLevelOff();
		Enemies_.push_back(Ptr);
	}
}

void EnemyController::Update()
{
	SetPosition(GameInfo::GetPlayerInfo()->PlayerPos_);

	IsSpawn_ = SpawnCounter_.Start(GameEngineTime::GetDeltaTime(static_cast<int>(TIME_GROUP::MONSTER)));

	if (true == IsSpawn_)
	{
		Spawn();
		SpawnCounter_.Reset();
	}

}

void EnemyController::Render()
{

}

void EnemyController::Spawn()
{

}
