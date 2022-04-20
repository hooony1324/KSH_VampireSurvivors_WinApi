#include "ShadeRed.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GameEnum.h"
#include "GameInfo.h"
#include "Vector2D.h"
#include "Counter.h"

ShadeRed::ShadeRed() 
	: Speed_(120.0f)
	, Hp_(100)
	, Hp_BarRed_(nullptr)
	, ShadeRed_(nullptr)
	, OtherBlockUp_(nullptr)
	, OtherBlockDown_(nullptr)
	, OtherBlockRight_(nullptr)
	, OtherBlockLeft_(nullptr)

{
}

ShadeRed::~ShadeRed() 
{
}

void ShadeRed::Start()
{
	//ShadeRed_ = CreateRenderer("ShadeRed_0.bmp");
	ShadeRed_ = CreateRenderer();
	ShadeRed_->CreateAnimation("ShadeRed_WalkLeft.bmp", "ShadeRed_WalkLeft", 0, 2, 0.2f, true);
	ShadeRed_->CreateAnimation("ShadeRed_WalkRight.bmp", "ShadeRed_WalkRight", 0, 2, 0.2f, true);
	ShadeRed_->CreateAnimation("ShadeRed_Dead.bmp", "ShadeRed_Dead", 0, 29, 0.1f, false);
	ShadeRed_->ChangeAnimation("ShadeRed_WalkRight");
	SetScale({ 100, 100 });

	ShadeRedCol_ = CreateCollision("Enemy", { 30, 30 });

	OtherBlockUp_ = CreateCollision("OtherGuard", { 36, 4 }, { 0, -20 });
	OtherBlockDown_ = CreateCollision("OtherGuard", { 36, 4 }, { 0, 20 });
	OtherBlockLeft_ = CreateCollision("OtherGuard", { 4, 36 }, { -20, 0 });
	OtherBlockRight_ = CreateCollision("OtherGuard", { 4, 36 }, { 20, 0 });

	// 디버그용
	CreateRenderer("hpbar_back.bmp", static_cast<int>(RENDER_ORDER::MONSTER), RenderPivot::CENTER, { 0, 40 });
	Hp_BarRed_ = CreateRenderer("hpbar.bmp", static_cast<int>(RENDER_ORDER::MONSTER), RenderPivot::CENTER, { 0, 40 });
	Hp_BarSize_ = Hp_BarRed_->GetScale();

	Counter1_.SetCount(5);
}

void ShadeRed::Update()
{
	float DeltaTime = GameEngineTime::GetDeltaTime(static_cast<int>(TIME_GROUP::MONSTER));

	if (Hp_ <= 0)
	{
		ShadeRedCol_->Death();
		ShadeRed_->ChangeAnimation("ShadeRed_Dead");

		if (true == Counter1_.Start(DeltaTime))
		{
			Death();
		}
		return;
	}

	Hit();

	float4 PlayerPos = GameInfo::GetPlayerInfo()->PlayerPos_;
	float4 EnemyPos = GetPosition();

	float4 DestDir = Vector2D::GetDirection(EnemyPos, PlayerPos);

	SetMove(DestDir * DeltaTime * Speed_);

	if (0 >= DestDir.x)
	{
		ShadeRed_->ChangeAnimation("ShadeRed_WalkLeft");
	}
	else
	{
		ShadeRed_->ChangeAnimation("ShadeRed_WalkRight");
	}

	BlockOther();

}

void ShadeRed::Render()
{
	float Ratio = Hp_ / 100.0f;
	float NewSizeX = Hp_BarSize_.x * Ratio;
	float4 Hp_BarPivot = float4{ 0 - ((Hp_BarSize_.x - NewSizeX) / 2), Hp_BarRed_->GetPivot().y };
	Hp_BarRed_->SetScale(float4{ NewSizeX, Hp_BarSize_.y });
	Hp_BarRed_->SetPivot(Hp_BarPivot);
}


void ShadeRed::Hit()
{
	// 무기 정보(공격력에 따라 데미지) 
	// 맞은 총알은 없애기
	if (false == ShadeRedCol_->CollisionCheck("PlayerAttack", CollisionType::Rect, CollisionType::Rect))
	{
		return;
	}

	Hp_ -= 10;

	// 넉백
	ShadeRed_->GetActor()->SetMove(float4::RIGHT);


}

void ShadeRed::BlockOther()
{
	// 위에 부딪힌 녀석 위로
	if (true == OtherBlockUp_->CollisionResult("Enemy", Others_, CollisionType::Rect, CollisionType::Rect))
	{
		Others_[0]->GetActor()->SetPosition(Others_[0]->GetActor()->GetPosition() + float4::UP * 2);
		Others_.clear();
	}

	if (true == OtherBlockDown_->CollisionResult("Enemy", Others_, CollisionType::Rect, CollisionType::Rect))
	{
		Others_[0]->GetActor()->SetPosition(Others_[0]->GetActor()->GetPosition() + float4::DOWN * 2);
		Others_.clear();
	}

	if (true == OtherBlockLeft_->CollisionResult("Enemy", Others_, CollisionType::Rect, CollisionType::Rect))
	{
		Others_[0]->GetActor()->SetPosition(Others_[0]->GetActor()->GetPosition() + float4::LEFT * 2);
		Others_.clear();

	}

	if (true == OtherBlockRight_->CollisionResult("Enemy", Others_, CollisionType::Rect, CollisionType::Rect))
	{
		Others_[0]->GetActor()->SetPosition(Others_[0]->GetActor()->GetPosition() + float4::RIGHT * 2);
		Others_.clear();
	}

}
