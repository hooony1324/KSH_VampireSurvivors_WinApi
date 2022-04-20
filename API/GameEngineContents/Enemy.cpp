#include "Enemy.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineBase/GameEngineSound.h>

#include "GameEnum.h"
#include "GameInfo.h"
#include "Vector2D.h"

#include "Counter.h"
#include "Projectile.h"

#include "ExpGem.h"

Enemy::Enemy()
	: Speed_(80.0f)
	, Hp_(100)
	, AttackCheck_(nullptr)
	, Renderer_(nullptr)
	, Hp_BarSize_(float4::ZERO)
	, Hp_BarRed_(nullptr)
	, Col_(nullptr)
	, OtherBlockLeft_(nullptr)
	, OtherBlockRight_(nullptr)
	, DestDir_(float4::ZERO)
{
}

Enemy::~Enemy()
{

}

void Enemy::Start()
{
	Renderer_ = CreateRenderer();
	Renderer_->CreateFolderAnimationTimeKey("Mud_WalkLeft.bmp", "Mud_WalkLeft", static_cast<int>(TIME_GROUP::MONSTER), 0, 3, 0.2f, true);
	Renderer_->CreateFolderAnimationTimeKey("Mud_WalkRight.bmp", "Mud_WalkRight", static_cast<int>(TIME_GROUP::MONSTER), 0, 3, 0.2f, true);
	Renderer_->CreateFolderAnimationTimeKey("Mud_Dead.bmp", "Mud_Dead", static_cast<int>(TIME_GROUP::MONSTER), 0, 27, 0.05f, true);
	Renderer_->ChangeAnimation("Mud_WalkRight");

	SetScale({ 100, 100 });

	Col_ = CreateCollision("Enemy", { 30, 45 });

	OtherBlockLeft_ = CreateCollision("OtherGuard", { 4, 45 }, { -16, 0 });
	OtherBlockRight_ = CreateCollision("OtherGuard", { 4, 45 }, { 16, 0 });



	// 디버그용
	CreateRenderer("hpbar_back.bmp", static_cast<int>(RENDER_ORDER::MONSTER), RenderPivot::CENTER, { 0, 40 });
	Hp_BarRed_ = CreateRenderer("hpbar.bmp", static_cast<int>(RENDER_ORDER::MONSTER), RenderPivot::CENTER, { 0, 40 });
	Hp_BarSize_ = Hp_BarRed_->GetScale();

	DeathCounter_.SetCount(1.0f);
}

void Enemy::Update()
{
	float DeltaTime = GameEngineTime::GetDeltaTime(static_cast<int>(TIME_GROUP::MONSTER));
	Pos_ = GetPosition();
	PlayerPos_ = GameInfo::GetPlayerInfo()->PlayerPos_;

	if (Hp_ <= 0)
	{
		Col_->Death();
		Renderer_->ChangeAnimation("Mud_Dead");

		if (true == DeathCounter_.Start(DeltaTime))
		{
			ExpGem* Gem = GetLevel()->CreateActor<ExpGem>(static_cast<int>(ACTOR_ORDER::ITEM), "ExpGem");
			Gem->SetType(GemType::BLUE);
			Gem->SetPosition(GetPosition());
			Death();
		}
		return;
	}


	DestDir_ = Vector2D::GetDirection(Pos_, PlayerPos_);

	BlockOther();
	Hit();

	SetMove((DestDir_ + KnockBackDir_) * DeltaTime * Speed_);

	if (0 >= DestDir_.x)
	{
		Renderer_->ChangeAnimation("Mud_WalkLeft");
	}
	else
	{
		Renderer_->ChangeAnimation("Mud_WalkRight");
	}


}

void Enemy::Render()
{

	// 체력 디버그용
	float Ratio = Hp_ / 100.0f;
	float NewSizeX = Hp_BarSize_.x * Ratio;
	float4 Hp_BarPivot = float4{ 0 - ((Hp_BarSize_.x - NewSizeX) / 2), Hp_BarRed_->GetPivot().y };
	Hp_BarRed_->SetScale(float4{ NewSizeX, Hp_BarSize_.y });
	Hp_BarRed_->SetPivot(Hp_BarPivot);

}

void Enemy::Hit()
{
	if (nullptr == Col_)
	{
		return;
	}

	if (KnockBackDir_.Len2D() >= 0)
	{
		KnockBackDir_ -= KnockBackDir_ * 0.1f;
	}

	if (false == Col_->CollisionResult("PlayerAttack", PlayerAttack_, CollisionType::Rect, CollisionType::Rect))
	{
		return;
	}

	// 맞았음
	GameEngineSound::SoundPlayOneShot("EnemyHit.mp3", 0);

	int Damage = dynamic_cast<Projectile*>(PlayerAttack_[0]->GetActor())->GetDamage();
	float4 BulletPos = PlayerAttack_[0]->GetCollisionPos();
	PlayerAttack_[0]->GetActor()->Death();
	PlayerAttack_.clear();

	Hp_ -= Damage;

	KnockBackDir_ = Vector2D::GetDirection(BulletPos, GetPosition()) * 5;

}

void Enemy::BlockOther()
{
	// Monster끼리 부딪히면
	// 서로 밀어냄

	if (true == Col_->CollisionResult("OtherGuard", Others_, CollisionType::Rect, CollisionType::Rect))
	{
		float4 OtherPos = Others_[0]->GetActor()->GetPosition();
		Others_[0]->GetActor()->SetMove(Vector2D::GetDirection(Pos_, OtherPos) * GameEngineTime::GetDeltaTime(static_cast<int>(TIME_GROUP::MONSTER)) * 85.0f);
		Others_.clear();
	}

}