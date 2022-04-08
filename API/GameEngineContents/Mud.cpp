#include "Mud.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
//#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "PlayerInfo.h"
#include "Vector2D.h"

Mud::Mud() 
	: Speed_(80.0f)
	, Hp_(100)
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

	// 디버그용
	CreateRenderer("hpbar_back.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, { 0, 40 });
	Hp_BarRed_ = CreateRenderer("hpbar.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, { 0, 40 });
	Hp_BarSize_ = Hp_BarRed_->GetScale();
}

void Mud::Update()
{
	float4 PlayerPos = PlayerInfo::GetInst()->GetCharacter()->Position_;
	float4 EnemyPos = GetPosition();
	float4 DestDir = Vector2D::GetDirection(EnemyPos, PlayerPos);
	

	Hit();

	SetMove(DestDir * GameEngineTime::GetDeltaTime() * Speed_);

	if (0 >= DestDir.x)
	{
		Mud_->ChangeAnimation("Mud_IdleLeft");
	}
	else
	{
		Mud_->ChangeAnimation("Mud_IdleRight");
	}

	BlockOther();

}

void Mud::Render()
{
	// 디버그용
	float Ratio = Hp_ / 100;
	float NewSizeX = Hp_BarSize_.x * Ratio;
	float4 Hp_BarPivot = float4{ 0 - ((Hp_BarSize_.x - NewSizeX) / 2), Hp_BarRed_->GetPivot().y };
	Hp_BarRed_->SetScale(float4{ NewSizeX, Hp_BarSize_.y });
	Hp_BarRed_->SetPivot(Hp_BarPivot);

}

void Mud::Hit()
{
	// 무기 정보(공격력에 따라 데미지) 
	// 맞은 총알은 없애기
	if (false == MudCol_->CollisionCheck("Bullet", CollisionType::Rect, CollisionType::Rect))
	{
		return;
	}

	Hp_ -= 10;

	// 넉백
	Mud_->GetActor()->SetMove(float4::RIGHT);
}

void Mud::BlockOther()
{
	// 위에 부딪힌 녀석 위로
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