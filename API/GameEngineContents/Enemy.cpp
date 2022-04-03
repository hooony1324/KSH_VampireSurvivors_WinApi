#include "Enemy.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
//#include <GameEngineBase/GameEngineDebug.h>

#include "PlayerInfo.h"
#include <cmath>

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

	float4 dst = PlayerPos - EnemyPos;
	float dstX = dst.x;
	float dstY = dst.y;
	float4 DestDir = { dst.x / sqrt( (float)(pow(dst.x, 2) + pow(dst.y, 2)) ), dstY / sqrt( (float)(pow(dst.x, 2) + pow(dst.y, 2)) ) };

	// {3, 3} <--> {5, 4}
	SetMove(DestDir * GameEngineTime::GetDeltaTime() * 100.0f);

}

