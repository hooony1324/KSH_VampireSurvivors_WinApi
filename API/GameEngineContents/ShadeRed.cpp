#include "ShadeRed.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "ObjectOrder.h"
#include "GameInfo.h"
#include "Vector2D.h"
#include "Counter.h"

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

	// 디버그용
	CreateRenderer("hpbar_back.bmp", static_cast<int>(RENDER_ORDER::MONSTER), RenderPivot::CENTER, { 0, 40 });
	Hp_BarRed_ = CreateRenderer("hpbar.bmp", static_cast<int>(RENDER_ORDER::MONSTER), RenderPivot::CENTER, { 0, 40 });
	Hp_BarSize_ = Hp_BarRed_->GetScale();

	Counter1_.SetCount(5);
}

void ShadeRed::Update()
{
	if (Hp_ <= 0)
	{
		ShadeRed_->ChangeAnimation("ShadeRed_Dead");

		if (true == Counter1_.Start(GameEngineTime::GetDeltaTime()))
		{
			Death();
		}
		return;
	}

	Hit();

	float4 PlayerPos = GameInfo::GetPlayerInfo()->PlayerPos_;
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
	if (false == ShadeRedCol_->CollisionCheck("Bullet", CollisionType::Rect, CollisionType::Rect))
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
