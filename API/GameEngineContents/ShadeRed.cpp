#include "ShadeRed.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "PlayerInfo.h"
#include "Vector2D.h"

ShadeRed::ShadeRed() 
	: Speed_(120.0f)
	, Hp_(100)
{
}

ShadeRed::~ShadeRed() 
{
}

void ShadeRed::Start()
{
	//ShadeRed_ = CreateRenderer("ShadeRed_0.bmp");
	ShadeRed_ = CreateRenderer();
	ShadeRed_->CreateAnimation("ShadeRed_IdleLeft.bmp", "ShadeRed_IdleLeft", 0, 2, 0.2f, true);
	ShadeRed_->CreateAnimation("ShadeRed_IdleRight.bmp", "ShadeRed_IdleRight", 0, 2, 0.2f, true);
	ShadeRed_->CreateAnimation("ShadeRed_Dead.bmp", "ShadeRed_Dead", 0, 29, 0.1f, false);
	ShadeRed_->ChangeAnimation("ShadeRed_IdleRight");
	SetScale({ 100, 100 });

	ShadeRedCol_ = CreateCollision("Monster", { 30, 30 });

	OtherBlockUp_ = CreateCollision("OtherGuard", { 36, 4 }, { 0, -20 });
	OtherBlockDown_ = CreateCollision("OtherGuard", { 36, 4 }, { 0, 20 });
	OtherBlockLeft_ = CreateCollision("OtherGuard", { 4, 36 }, { -20, 0 });
	OtherBlockRight_ = CreateCollision("OtherGuard", { 4, 36 }, { 20, 0 });
}

void ShadeRed::Update()
{
	float4 PlayerPos = PlayerInfo::GetInst()->GetCharacter()->Position_;
	float4 EnemyPos = GetPosition();

	float4 DestDir = Vector2D::GetDirection(EnemyPos, PlayerPos);

	SetMove(DestDir * GameEngineTime::GetDeltaTime() * Speed_);

	if (0 >= DestDir.x)
	{
		ShadeRed_->ChangeAnimation("ShadeRed_IdleLeft");
	}
	else
	{
		ShadeRed_->ChangeAnimation("ShadeRed_IdleRight");
	}

	BlockOther();

}

void ShadeRed::Render()
{
}

void ShadeRed::BlockOther()
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
