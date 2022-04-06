#include "EnemyController.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
//#include <GameEngineBase/GameEngineDebug.h>
#include "PlayerInfo.h"

EnemyController::EnemyController() 
	: EnemyCollectorL_(nullptr)
	, EnemyCollectorR_(nullptr)
{
}

EnemyController::~EnemyController() 
{
}

void EnemyController::Start()
{
	// 몬스터가 충돌하면 리스폰
	EnemyCollectorL_ = CreateCollision("EnemyCollector", { 30, 700 }, { -500, 0 });
	EnemyCollectorR_ = CreateCollision("EnemyCollector", { 30, 700 }, { 500, 0 });

	EnemySpawnerL_ = EnemyCollectorL_ = CreateCollision("EnemyCollector", { 30, 650 }, { -400, 0 });
	EnemySpawnerR_ = EnemyCollectorL_ = CreateCollision("EnemyCollector", { 30, 650 }, { 400, 0 });
}

void EnemyController::Update()
{
}

void EnemyController::Render()
{

}
