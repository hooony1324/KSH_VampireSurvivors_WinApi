#include "EnemyController.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineBase/GameEngineInput.h>

#include "GameInfo.h"
#include "GameEnum.h"
#include "Enemy.h"
#include "Boss.h"
#include "ShadeRed.h"

const int MaxEnemySpawn = 50;
int EnemyController::LiveEnemyNum = 0;
const float SpawnCycle = 5.0f;

const int PointNumX = 10;
const int PointNumY = 15;
const float CollisionSizeX = 40;
const float CollisionSizeY = 45;

float4 SpawnPoint[PointNumY][PointNumX] = { float4::ZERO, };
bool SpawnPointPicked[PointNumY][PointNumX] = { false, };

const float WAVE_TIME = 20.0f; // �ٸ� ������ Enemy�� �ٲ�� �ֱ�

EnemyController::EnemyController() 
	: EnemiesIndex(0)
	, IsSpawnTime_(false)
	, BossIndex_(0)
{
	// ���� ���� ��ġ�� �ʵ���
	// ������ ������� 40 x 45(����, ����)
	for (int y = 0; y < PointNumY; y++)
	{
		for (int x = 0; x < PointNumX; x++)
		{
			SpawnPoint[y][x] = float4{ x * CollisionSizeX, y * CollisionSizeY };
		}
	}
}

EnemyController::~EnemyController() 
{
}

void EnemyController::Start()
{
	// ������ �� �ʿ�
	LiveEnemyNum = 0;
	Enemy::EnemyNameListIndex = 0;
	Boss::BossIndex_ = 0;
	Boss::IsReaperSpawn_ = false;

	// �Ϲݸ�
	Enemies_.reserve(MaxEnemySpawn);

	for (int i = 0; i < MaxEnemySpawn; i++)
	{
		Enemy* Ptr = GetLevel()->CreateActor<Enemy>(static_cast<int>(ACTOR_ORDER::MONSTER), "Enemy");
		Ptr->SetPosition(float4{ 700 + static_cast<float>(i) * 50, -40 });
		Ptr->Off();
		Ptr->SetDead();		// ���ʹ� ����ִ� ����
		Ptr->NextLevelOff();
		Enemies_.push_back(Ptr);
	}

	SpawnCounter_.SetCount(0);
	SpawnMax_ = 7;
	SpawnNum_ = 0;
	SpawnPosBase_ = float4{ 700, -400 };

	// ����, ����� ��
	BossCounter_.SetCount(0);
	ShadeRedCounter_.SetCount(0);

	// ���̺� ���� ���� ����
	WaveIndex_ = 0;

	NextLevelOff();
}

void EnemyController::Update()
{
	float DeltaTime = GameEngineTime::GetDeltaTime(static_cast<int>(TIME_GROUP::MONSTER));
	Time_ += DeltaTime;
	WaveIndexUpdate();

	SetPosition(float4{ GameInfo::GetPlayerInfo()->PlayerPos_.x, 840 });

	
	IsSpawnTime_ = SpawnCounter_.Start(DeltaTime);
	if (true == IsSpawnTime_)
	{
		SpawnWave();
		ChangeSpawnPosBase();
		SpawnCounter_.SetCount(5);

	}

	SpawnBoss(BossCounter_.Start(DeltaTime));
	SpawnReaperButton();

	SpawnShadeRed(ShadeRedCounter_.Start(DeltaTime));
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

		// �׾������� ��ȯ
		if (true == Ptr->IsDead())
		{
			Ptr->SetLive();
			
			Ptr->SetEnemy(WaveIndex_);

			// ���� ��ġ �ʹ� ������ �ȵ�
			float4 RandomPos = GetSpawnPos();
			Ptr->SetPosition(GetPosition() + SpawnPosBase_ + RandomPos);

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

	// ���� �ߺ� �ȵǵ���
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

void EnemyController::ChangeSpawnPosBase()
{
	if ( 0 < SpawnPosBase_.ix())
	{
		SpawnPosBase_.x = -1400;
	}
	else
	{
		SpawnPosBase_.x = 700;
	}
}

void EnemyController::SpawnReaperButton()
{
	if (true == GameEngineInput::GetInst()->IsDown("SpawnReaper"))
	{
		Boss::IsReaperSpawn_ = true;
	}
}

void EnemyController::SpawnShadeRed(bool _CounterEnd)
{
	if (false == _CounterEnd)
	{
		return;
	}

	int SpawnNum = (WaveIndex_ % 10);

	for (int i = 0; i < SpawnNum; i++)
	{
		// ShadeRed��ȯ
		GameEngineActor* RedPtr = GetLevel()->CreateActor<ShadeRed>(static_cast<int>(ACTOR_ORDER::MONSTER));
		ShadeRed* Red = dynamic_cast<ShadeRed*>(RedPtr);

		Red->SetPosition(GetPosition() + SpawnPosBase_ + GetSpawnPos());
	}

	ShadeRedCounter_.SetCount(60);
}

void EnemyController::SpawnBoss(bool _BossCounterEnd)
{
	if (true == _BossCounterEnd)
	{
		GameEngineActor* Ptr = GetLevel()->CreateActor<Boss>(static_cast<int>(ACTOR_ORDER::MONSTER));
		Boss* BossPtr = dynamic_cast<Boss*>(Ptr);

		// ��ȯ ��ġ ����
		BossPtr->SetPosition(GetPosition() + SpawnPosBase_ + GetSpawnPos());

		// ���� ���� ��ȯ �ֱ�
		BossCounter_.SetCount(40.0f);

		// ���� ���� ����
		Boss::BossIndex_ += 1;
		// �ε��� ����
	}

}