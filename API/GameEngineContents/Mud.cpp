#include "Mud.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
//#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "PlayerInfo.h"

Mud::Mud() 
	: Speed_(80.0f)
{
}

Mud::~Mud() 
{

}

void Mud::PushOther()
{	
	
}

void Mud::Start()
{
	//Mud_ = CreateRenderer("Mud_0.bmp");
	Mud_->CreateAnimation();
	SetScale({ 100, 100 });

	MudCol_ = CreateCollision("Monster", { 30, 30 });
	
	OtherBlockUp_ = CreateCollision("OtherGuard", { 2, 32}, {0, -16});
	OtherBlockDown_ = CreateCollision("OtherGuard", { 2, 32}, {0, 16});
	OtherBlockLeft_ = CreateCollision("OtherGuard", { 32, 2}, {-16, 0});
	OtherBlockRight_ = CreateCollision("OtherGuard", { 32, 2}, {16, 0});
}

void Mud::Update()
{
	float4 PlayerPos = PlayerInfo::GetInst()->GetCharacter()->Position_;
	float4 EnemyPos = GetPosition();

	float4 DestDir = float4::Normalized(EnemyPos, PlayerPos);

	SetMove(DestDir * GameEngineTime::GetDeltaTime() * Speed_);
	PushOther();

}

void Mud::Render()
{
}
