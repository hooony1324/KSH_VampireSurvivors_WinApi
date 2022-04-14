#include "EnemyController.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>

#include "GameInfo.h"

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
	// ���Ͱ� �浹�ϸ� ������
	EnemyCollectorL_ = CreateCollision("EnemyCollector", { 30, 700 }, { -500, 0 });
	EnemyCollectorR_ = CreateCollision("EnemyCollector", { 30, 700 }, { 500, 0 });

	// �浹ü �ƴѵ� �׳� ǥ�ÿ�����
	EnemySpawnerL_ = CreateCollision("EnemySpawner", { 30, 650 }, { -400, 0 });
	EnemySpawnerR_ = CreateCollision("EnemySpawner", { 30, 650 }, { 400, 0 });

}

void EnemyController::Update()
{
	SetPosition(GameInfo::GetPlayerInfo()->PlayerPos_);
}

void EnemyController::Render()
{

}
