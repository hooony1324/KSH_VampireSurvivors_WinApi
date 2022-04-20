#include "Mud.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
//#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineBase/GameEngineSound.h>

#include "GameEnum.h"
#include "GameInfo.h"
#include "Vector2D.h"

#include "Counter.h"
#include "Projectile.h"

#include "ExpGem.h"

Mud::Mud() 
	: Speed_(80.0f)
	, Hp_(100)
	, AttackCheck_(nullptr)
	, Mud_(nullptr)
	, Hp_BarSize_(float4::ZERO)
	, Hp_BarRed_(nullptr)
	, MudCol_(nullptr)
	, OtherBlockUp_(nullptr)
	, OtherBlockDown_(nullptr)
	, OtherBlockLeft_(nullptr)
	, OtherBlockRight_(nullptr)
{
}

Mud::~Mud() 
{

}

void Mud::Start()
{
	Mud_ = CreateRenderer();
	Mud_->CreateFolderAnimationTimeKey("Mud_WalkLeft.bmp", "Mud_WalkLeft", static_cast<int>(TIME_GROUP::MONSTER), 0, 3, 0.2f, true);
	Mud_->CreateFolderAnimationTimeKey("Mud_WalkRight.bmp", "Mud_WalkRight", static_cast<int>(TIME_GROUP::MONSTER), 0, 3, 0.2f, true);
	Mud_->CreateFolderAnimationTimeKey("Mud_Dead.bmp", "Mud_Dead", static_cast<int>(TIME_GROUP::MONSTER), 0, 27, 0.05f, true);
	Mud_->ChangeAnimation("Mud_WalkRight");

	SetScale({ 100, 100 });

	MudCol_ = CreateCollision("Enemy", { 35, 35 });
	
	OtherBlockUp_ = CreateCollision("OtherGuard", { 30, 4}, {0, -16});
	OtherBlockDown_ = CreateCollision("OtherGuard", { 30, 4}, {0, 16});
	OtherBlockLeft_ = CreateCollision("OtherGuard", { 4, 30 }, { -16, 0 });
	OtherBlockRight_ = CreateCollision("OtherGuard", { 4, 30}, {16, 0});

	// 디버그용
	CreateRenderer("hpbar_back.bmp", static_cast<int>(RENDER_ORDER::MONSTER), RenderPivot::CENTER, { 0, 40 });
	Hp_BarRed_ = CreateRenderer("hpbar.bmp", static_cast<int>(RENDER_ORDER::MONSTER), RenderPivot::CENTER, { 0, 40 });
	Hp_BarSize_ = Hp_BarRed_->GetScale();

	Counter1_.SetCount(1.0f);


}

void Mud::Update()
{

	float DeltaTime = GameEngineTime::GetDeltaTime(static_cast<int>(TIME_GROUP::MONSTER));
	if (Hp_ <= 0)
	{
		MudCol_->Death();
		Mud_->ChangeAnimation("Mud_Dead");

		if (true == Counter1_.Start(DeltaTime))
		{
			ExpGem* Gem = GetLevel()->CreateActor<ExpGem>(static_cast<int>(ACTOR_ORDER::ITEM), "ExpGem");
			Gem->SetType(GemType::BLUE);
			Gem->SetPosition(GetPosition());
			Death();
		}
		return;
	}

	PlayerPos_ = GameInfo::GetPlayerInfo()->PlayerPos_;
	float4 EnemyPos = GetPosition();
	float4 DestDir = Vector2D::GetDirection(EnemyPos, PlayerPos_);

	BlockOther();
	Hit();

	SetMove((DestDir + KnockBackDir_) * DeltaTime * Speed_);

	if (0 >= DestDir.x)
	{
		Mud_->ChangeAnimation("Mud_WalkLeft");
	}
	else
	{
		Mud_->ChangeAnimation("Mud_WalkRight");
	}


}

void Mud::Render()
{

	// 체력 디버그용
	float Ratio = Hp_ / 100.0f ;
	float NewSizeX = Hp_BarSize_.x * Ratio;
	float4 Hp_BarPivot = float4{ 0 - ((Hp_BarSize_.x - NewSizeX) / 2), Hp_BarRed_->GetPivot().y };
	Hp_BarRed_->SetScale(float4{ NewSizeX, Hp_BarSize_.y });
	Hp_BarRed_->SetPivot(Hp_BarPivot);

}

void Mud::Hit()
{
	if (nullptr == MudCol_)
	{
		return;
	}

	if (KnockBackDir_.Len2D() >= 0)
	{
		KnockBackDir_ -= KnockBackDir_ * 0.1f;
	}

	std::vector<GameEngineCollision*> HitBullet;
	if (false == MudCol_->CollisionResult("PlayerAttack", HitBullet, CollisionType::Rect, CollisionType::Rect))
	{
		return;
	}

	// 맞았음
	GameEngineSound::SoundPlayOneShot("EnemyHit.mp3", 0);

	int Damage = dynamic_cast<Projectile*>(HitBullet[0]->GetActor())->GetDamage();
	HitBullet[0]->GetActor()->Death();
	HitBullet.clear();

	Hp_ -= Damage;

	// 플레이어 방향과 반대로
	KnockBackDir_ = Vector2D::GetDirection(PlayerPos_ , GetPosition()) * 25;

}

void Mud::BlockOther()
{
	// Monster끼리 부딪히면
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