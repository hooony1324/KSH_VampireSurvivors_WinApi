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
	ShadeRed_ = CreateRenderer();
	//ShadeRed_->CreateAnimation("ShadeRed_WalkLeft.bmp", "ShadeRed_WalkLeft", 0, 2, 0.2f, true);
	//ShadeRed_->CreateAnimation("ShadeRed_WalkRight.bmp", "ShadeRed_WalkRight", 0, 2, 0.2f, true);
	//ShadeRed_->CreateAnimation("ShadeRed_Dead.bmp", "ShadeRed_Dead", 0, 29, 0.1f, false);
	//ShadeRed_->ChangeAnimation("ShadeRed_WalkRight");
	SetScale({ 100, 100 });

	ShadeRedCol_ = CreateCollision("Enemy", { 30, 30 });

	OtherBlockUp_ = CreateCollision("OtherGuard", { 36, 4 }, { 0, -20 });
	OtherBlockDown_ = CreateCollision("OtherGuard", { 36, 4 }, { 0, 20 });
	OtherBlockLeft_ = CreateCollision("OtherGuard", { 4, 36 }, { -20, 0 });
	OtherBlockRight_ = CreateCollision("OtherGuard", { 4, 36 }, { 20, 0 });


	DeathCounter_.SetCount(5);
}

void ShadeRed::Update()
{
	float DeltaTime = GameEngineTime::GetDeltaTime(static_cast<int>(TIME_GROUP::MONSTER));

	if (Hp_ <= 0)
	{
		ShadeRedCol_->Death();
		ShadeRed_->ChangeAnimation("ShadeRed_Dead");

		if (true == DeathCounter_.Start(DeltaTime))
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


}
