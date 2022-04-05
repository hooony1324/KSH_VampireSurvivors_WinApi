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

void Mud::BlockOther()
{	
	// À§¿¡ ºÎµúÈù ³à¼® À§·Î
	if (true == OtherBlockUp_->CollisionResult("Monster", Others_, CollisionType::Rect, CollisionType::Rect))
	{
		Others_[0]->GetActor()->SetPosition(Others_[0]->GetActor()->GetPosition() + float4::UP*2);
		Others_.clear();
	}

	if (true == OtherBlockDown_->CollisionResult("Monster", Others_, CollisionType::Rect, CollisionType::Rect))
	{
		Others_[0]->GetActor()->SetPosition(Others_[0]->GetActor()->GetPosition() + float4::DOWN*2);
		Others_.clear();
	}

	if (true == OtherBlockLeft_->CollisionResult("Monster", Others_, CollisionType::Rect, CollisionType::Rect))
	{
		Others_[0]->GetActor()->SetPosition(Others_[0]->GetActor()->GetPosition() + float4::LEFT*2);
		Others_.clear();
		
	}

	if (true == OtherBlockRight_->CollisionResult("Monster", Others_, CollisionType::Rect, CollisionType::Rect))
	{
		Others_[0]->GetActor()->SetPosition(Others_[0]->GetActor()->GetPosition() + float4::RIGHT*2);
		Others_.clear();
	}


}

void Mud::Start()
{
	//Mud_ = CreateRenderer("Mud_0.bmp");
	Mud_ = CreateRenderer();
	Mud_->CreateAnimation("Mud_Idle.bmp", "Mud_Idle", 0, 3, 0.2f, true);
	Mud_->ChangeAnimation("Mud_Idle");
	SetScale({ 100, 100 });

	MudCol_ = CreateCollision("Monster", { 30, 30 });
	
	OtherBlockUp_ = CreateCollision("OtherGuard", { 36, 4}, {0, -20});
	OtherBlockDown_ = CreateCollision("OtherGuard", { 36, 4}, {0, 20});
	OtherBlockLeft_ = CreateCollision("OtherGuard", { 4, 36 }, { -20, 0 });
	OtherBlockRight_ = CreateCollision("OtherGuard", { 4, 36}, {20, 0});
}

void Mud::Update()
{
	float4 PlayerPos = PlayerInfo::GetInst()->GetCharacter()->Position_;
	float4 EnemyPos = GetPosition();

	float4 DestDir = float4::Normalized(EnemyPos, PlayerPos);

	SetMove(DestDir * GameEngineTime::GetDeltaTime() * Speed_);
	BlockOther();

}

void Mud::Render()
{
}
