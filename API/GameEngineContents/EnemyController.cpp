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

const int PointNumX = 10;
const int PointNumY = 15;
const float CollisionSizeX = 40;
const float CollisionSizeY = 45;

float4 SpawnPoint[PointNumY][PointNumX] = { float4::ZERO, };
bool SpawnPointPicked[PointNumY][PointNumX] = { false, };

EnemyController::EnemyController() 
	: EnemyCollectorL_(nullptr)
	, EnemyCollectorR_(nullptr)
	, EnemySpawnerL_(nullptr)
	, EnemySpawnerR_(nullptr)
	, EnemiesIndex(0)
	, IsSpawnTime_(false)
{
	// ���� ���� ��ġ�� �ʵ���
	// ������ ������� 40 x 45(����, ����)
	for (int y = 0; y < PointNumY; y++)
	{
		for (int x = 0; x < PointNumX; x++)
		{
			// x: 0 y: 0 -> float4 {0, 0}
			// x: 1 y: 0 -> float4 {40, 0}
			// x: 2 y: 3 -> float4 {40*x, 45*y}
			SpawnPoint[y][x] = float4{ x * CollisionSizeX, y * CollisionSizeY };
		}
	}
}

EnemyController::~EnemyController() 
{
}

void EnemyController::Start()
{
	// ���� ���� �ֱ�


	// ���Ͱ� �浹�ϸ� ������
	EnemyCollectorL_ = CreateCollision("EnemyCollector", { 30, 700 }, { -500, 0 });
	EnemyCollectorR_ = CreateCollision("EnemyCollector", { 30, 700 }, { 500, 0 });

	// �浹ü �ƴѵ� �׳� ǥ�ÿ�����
	//EnemySpawnerL_ = CreateCollision("EnemySpawner", { 100, 650 }, { -400, 0 });
	EnemySpawnerR_ = CreateCollision("EnemySpawner", { 400, 675 }, { 400, 0 });


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
			
			// ���� ��ġ ������ġ �ʹ� ������ �ȵ�
			float4 Pos = GetSpawnPos();
			Ptr->SetPosition(GetPosition() + float4{ 100 , -400} + Pos);

			SpawnNum_++;
			EnemiesIndex++;
		}

		if (EnemiesIndex == static_cast<int>(Enemies_.size()))
		{
			EnemiesIndex = 0;
		}
	}

	// ���� �̱� �ߺ� �ȵǵ���
	for (int y = 0; y < PointNumY; y++)
	{
		for (int x = 0; x < PointNumX; x++)
		{
			SpawnPointPicked[y][x] = false;
		}
	}
}

float4 EnemyController::GetSpawnPos()
{
	// �ʹ� ������ ��ȯ�Ǹ� �پ����
	
	GameEngineRandom Random;
	bool Pick = false;
	int IndexX;
	int IndexY;

	while (false == Pick)
	{
		IndexX = Random.RandomInt(0, PointNumX - 1);
		IndexY = Random.RandomInt(0, PointNumY - 1);
		if (false == SpawnPointPicked[IndexY][IndexX])
		{
			SpawnPointPicked[IndexY][IndexX] = true;
			Pick = true;
		}
	}

	return SpawnPoint[IndexY][IndexX];
	
}
