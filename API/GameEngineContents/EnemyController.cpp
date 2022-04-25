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
int EnemyController::LiveEnemyNum = 0;
const float SpawnCycle = 5.0f;

const int PointNumX = 10;
const int PointNumY = 15;
const float CollisionSizeX = 40;
const float CollisionSizeY = 45;

float4 SpawnPoint[PointNumY][PointNumX] = { float4::ZERO, };
bool SpawnPointPicked[PointNumY][PointNumX] = { false, };

const float WAVE_TIME = 30.0f;

EnemyController::EnemyController() 
	: EnemiesIndex(0)
	, IsSpawnTime_(false)
	, BossIndex_(0)
{
	// 몬스터 스폰 겹치지 않도록
	// 몬스터의 사이즈는 40 x 45(가로, 세로)
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

	// 일반몹
	Enemies_.reserve(MaxEnemySpawn);

	for (int i = 0; i < MaxEnemySpawn; i++)
	{
		Enemy* Ptr = GetLevel()->CreateActor<Enemy>(static_cast<int>(ACTOR_ORDER::MONSTER), "Enemy");
		Ptr->SetPosition(float4{ 700 + static_cast<float>(i) * 50, -40 });
		Ptr->Off();
		Ptr->SetDead();
		Ptr->NextLevelOff();
		Enemies_.push_back(Ptr);
	}

	SpawnCounter_.SetCount(0);
	SpawnMax_ = 7;
	SpawnNum_ = 0;
	SpawnPosR_ = float4{ GameEngineWindow::GetScale().Half().x , -400};

	// 보스, 스페셜 몹
	BossCounter_.SetCount(0);

	// 웨이브 시작 몬스터 설정
	WaveIndex_ = 0;

	NextLevelOff();
}

void EnemyController::Update()
{
	float DeltaTime = GameEngineTime::GetDeltaTime(static_cast<int>(TIME_GROUP::TIMER));
	Time_ += DeltaTime;
	WaveIndexUpdate();

	SetPosition(float4{ GameInfo::GetPlayerInfo()->PlayerPos_.x, 840 });

	
	IsSpawnTime_ = SpawnCounter_.Start(DeltaTime);
	if (true == IsSpawnTime_)
	{
		SpawnWave();
		SpawnCounter_.SetCount(5);
	}

	SpawnBoss(BossCounter_.Start(DeltaTime));

}

void EnemyController::Render()
{

}

void EnemyController::WaveIndexUpdate()
{
	if (Time_ >= WAVE_TIME)
	{
		Time_ = 0.0f;
		WaveIndex_++;
	}
}

void EnemyController::SpawnWave()
{
	while (SpawnNum_ < SpawnMax_)
	{
		if (LiveEnemyNum >= MaxEnemySpawn)
		{
			return;
		}
		Enemy* Ptr = Enemies_[EnemiesIndex];

		// 죽어있으면 소환
		if (true == Ptr->IsDead())
		{
			Ptr->On();
			Ptr->SetLive();

			
			Ptr->SetEnemy(WaveIndex_);

			// 생성 위치 너무 가까우면 안됨
			float4 Pos = GetSpawnPos();
			Ptr->SetPosition(GetPosition() + SpawnPosR_ + Pos);

			SpawnNum_++;
			LiveEnemyNum++;
		}
		EnemiesIndex++;

		if (EnemiesIndex == static_cast<int>(Enemies_.size()))
		{
			EnemiesIndex = 0;
		}
	}

	SpawnNum_ = 0;

	// 랜덤 중복 안되도록
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
	// 너무 가까이 소환되면 붙어버림
	
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

void EnemyController::SpawnBoss(bool _BossCounter)
{

	BossCounter_.SetCount(60.0f);
}