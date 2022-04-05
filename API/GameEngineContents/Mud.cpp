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
	, Hp_(10)
{
}

Mud::~Mud() 
{

}

void Mud::Start()
{
	//Mud_ = CreateRenderer("Mud_0.bmp");
	Mud_ = CreateRenderer();
	Mud_->CreateAnimation("Mud_IdleLeft.bmp", "Mud_IdleLeft", 0, 3, 0.2f, true);
	Mud_->CreateAnimation("Mud_IdleRight.bmp", "Mud_IdleRight", 0, 3, 0.2f, true);
	Mud_->CreateAnimation("Mud_Dead.bmp", "Mud_Dead", 0, 27, 0.1f, false);
	Mud_->ChangeAnimation("Mud_IdleRight");
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

void Mud::BlockOther()
{
	// À§¿¡ ºÎµúÈù ³à¼® À§·Î
	if (true == OtherBlockUp_->CollisionResult("Monster", Others_, CollisionType::Rect, CollisionType::Rect))
	{
		Others_[0]->GetActor()->SetPosition(Others_[0]->GetActor()->GetPosition() + float4::UP * 2);
		Others_.clear();
	}

	if (true == OtherBlockDown_->CollisionResult("Monster", Others_, CollisionType::Rect, CollisionType::Rect))
	{
		Others_[0]->GetActor()->SetPosition(Others_[0]->GetActor()->GetPosition() + float4::DOWN * 2);
		Others_.clear();
	}

	if (true == OtherBlockLeft_->CollisionResult("Monster", Others_, CollisionType::Rect, CollisionType::Rect))
	{
		Others_[0]->GetActor()->SetPosition(Others_[0]->GetActor()->GetPosition() + float4::LEFT * 2);
		Others_.clear();

	}

	if (true == OtherBlockRight_->CollisionResult("Monster", Others_, CollisionType::Rect, CollisionType::Rect))
	{
		Others_[0]->GetActor()->SetPosition(Others_[0]->GetActor()->GetPosition() + float4::RIGHT * 2);
		Others_.clear();
	}

}