#include "Enemy.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
//#include <GameEngineBase/GameEngineDebug.h>

#include "PlayerInfo.h"

Enemy::Enemy() 
{
}

Enemy::~Enemy() 
{
}

void Enemy::Update()
{
	float4 PlayerPos = PlayerInfo::GetInst()->GetCharacter()->Position_; 
	float4 EnemyPos = GetPosition();

	float4 DestDir = float4::Normalized(EnemyPos, PlayerPos);

	SetMove(DestDir * GameEngineTime::GetDeltaTime() * 100.0f);

}

