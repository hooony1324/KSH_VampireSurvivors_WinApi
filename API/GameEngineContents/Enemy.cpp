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
#include "PlayLevel.h"
#include "EnemyController.h"

GameEngineImage* Enemy::MapColImage_ = nullptr;
std::vector<std::string> EnemyNameList = {"Mud", "Medusa", "Ecto", "Mummy"};
int Enemy::EnemyNameListIndex = 0;

Enemy::Enemy()
	: Speed_(80.0f)
	, Hp_(10)
	, Renderer_(nullptr)
	, Col_(nullptr)
	, OtherBlockLeft_(nullptr)
	, OtherBlockRight_(nullptr)
	, DestDir_(float4::ZERO)
	, Dead_(false)
{
}

Enemy::~Enemy()
{

}

void Enemy::SetEnemy(int _Index)
{
	EnemyNameListIndex = _Index;

	if (EnemyNameListIndex >= static_cast<int>(EnemyNameList.size()))
	{
		int a = static_cast<int>(EnemyNameList.size());
		EnemyNameListIndex = EnemyNameListIndex % static_cast<int>(EnemyNameList.size());
	}

	EnemyName_ = EnemyNameList[EnemyNameListIndex];
	Renderer_->ChangeAnimation(EnemyName_ + "_WalkRight");
	KnockBackDir_ = float4::ZERO;
}

void Enemy::Start()
{
	MapColImage_ = PlayLevel::MapColImage_;

	EnemyName_ = EnemyNameList[EnemyNameListIndex];
	
	Renderer_ = CreateRenderer();
	SetRenderer();

	Renderer_->ChangeAnimation(EnemyName_ + "_WalkRight");

	SetScale({ 100, 100 });

	Col_ = CreateCollision("Enemy", { 28, 45 });

	Others_.reserve(4);
	OtherBlockLeft_ = CreateCollision("OtherGuard", { 4, 45 }, { -18, 0 });
	OtherBlockRight_ = CreateCollision("OtherGuard", { 4, 45 }, { 18, 0 });

	DeathCounter_.SetCount(1.0f);
	UpDownCounter_.SetCount(1.0f);

	NextLevelOff();

	// Medusa 움직임
	UpDown_ = 1;

	// 되살아날때 더 강해진다
	DeadCount_ = 0;
}

void Enemy::Update()
{
	DeltaTime_ = GameEngineTime::GetDeltaTime(static_cast<int>(TIME_GROUP::MONSTER));
	Pos_ = GetPosition();

	// 죽었음
	EnemyDead();
	if (true == Dead_)
	{
		return;
	}

	// 살아있음
	EnemyMove();
	BlockOther();
	Hit();
	UpdateHeadDir();
}

void Enemy::Render()
{

}

void Enemy::Hit()
{
	if (nullptr == Col_)
	{
		return;
	}

	if (KnockBackDir_.Len2D() >= 0.0f)
	{
		KnockBackDir_ -= KnockBackDir_ * 0.25f;
	}

	if (false == Col_->CollisionResult("PlayerAttack", PlayerAttack_, CollisionType::Rect, CollisionType::Rect))
	{
		return;
	}

	// 맞았음
	GameEngineSound::SoundPlayOneShot("EnemyHit.mp3", 0);

	float Damage = dynamic_cast<Projectile*>(PlayerAttack_[0]->GetActor())->GetDamage();
	float4 BulletPos = PlayerAttack_[0]->GetCollisionPos();
	PlayerAttack_[0]->GetActor()->Death();
	PlayerAttack_.clear();

	Hp_ -= Damage;

	// 넉백 방향
	KnockBackDir_ = Vector2D::GetDirection(BulletPos, Pos_);

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

void Enemy::EnemyDead()
{
	if (Hp_ > 0)
	{
		return;
	}

	if (false == Dead_)
	{
		GameInfo::GetPlayerInfo()->KillCount_ += 1;
		Renderer_->ChangeAnimation(EnemyName_ + "_Dead");
		KnockBackDir_.Normal2D();
		Dead_ = true;
	}


	// 죽으면서 밀려남
	SetMove(KnockBackDir_ * DeltaTime_ * 90.0f);

	if (true == DeathCounter_.Start(DeltaTime_))
	{
		ExpGem* Gem = GetLevel()->CreateActor<ExpGem>(static_cast<int>(ACTOR_ORDER::ITEM), "ExpGem");
		Gem->SetType(GemType::BLUE);
		Gem->SetPosition(Pos_);
		
		Off();
		EnemyController::LiveEnemyNum -= 1;
		SetPosition(float4{ Pos_.x, -40 });
		DeadCount_++;
		Hp_ = static_cast<float>(100 + (DeadCount_ * 20));

	}

	
}

void Enemy::EnemyMove()
{
	PlayerPos_ = GameInfo::GetPlayerInfo()->PlayerPos_;
	DestDir_ = Vector2D::GetDirection(Pos_, PlayerPos_);

	// 현재 몬스터가 Medusa 라면
	if (0 == EnemyName_.compare("Medusa"))
	{
		Speed_ = 200.0f;
		if (true == UpDownCounter_.Start(DeltaTime_))
		{
			UpDown_ *= -1;
			UpDownCounter_.Reset();
		}

		DestDir_ = float4{ DestDir_.x, UpDown_};
	}

	float Speed = MapColCheck(Speed_);
	SetMove((DestDir_ + (KnockBackDir_ * 40.0f)) * DeltaTime_ * Speed);
}

void Enemy::UpdateHeadDir()
{

	if (0 >= DestDir_.x)
	{
		Renderer_->ChangeAnimation(EnemyName_ + "_WalkLeft");
	}
	else
	{
		Renderer_->ChangeAnimation(EnemyName_ + "_WalkRight");
	}

}


float Enemy::MapColCheck(float _Speed)
{

	int EnemyPosX = GetPosition().ix() % MapColImage_->GetScale().ix();
	if (EnemyPosX < 0)
	{
		EnemyPosX = EnemyPosX + MapColImage_->GetScale().ix();
	}

	float4 EnemyMapColPos = { static_cast<float>(EnemyPosX), GetPosition().y };
	int ColorTop = MapColImage_->GetImagePixel(EnemyMapColPos + float4{ 0, -25 });
	int ColorBot = MapColImage_->GetImagePixel(EnemyMapColPos + float4{ 0, 25 });
	int ColorLeft = MapColImage_->GetImagePixel(EnemyMapColPos + float4{ -25, 0 });
	int ColorRight = MapColImage_->GetImagePixel(EnemyMapColPos + float4{ 25, 0 });

	// 스폰 됐을 때콜리전 맵 안에 갇혀있으면 빠져나가야함
	int Trapped = ColorTop + ColorBot + ColorLeft + ColorRight;
	if (Trapped <= static_cast<int>(RGB(255, 255, 255)) * 1 )
	{
		// 3개 이상이 RGB(0, 0, 0)인 경우(갇힘) 움직일 수 있다
		return _Speed;
	}
	
	if (RGB(0, 0, 0) == ColorTop && DestDir_.y < 0.0f)
	{
		return 0.0f;
	}

	if (RGB(0, 0, 0) == ColorBot && DestDir_.y > 0.0f)
	{
		return 0.0f;
	}

	if (RGB(0, 0, 0) == ColorLeft && DestDir_.x < 0.0f)
	{
		return 0.0f;
	}

	if (RGB(0, 0, 0) == ColorRight && DestDir_.x > 0.0f)
	{
		return 0.0f;
	}

	return _Speed;
}



void Enemy::SetRenderer()
{
	for (int i = 0; i < static_cast<int>(EnemyNameList.size()); i++)
	{
		std::string EnemyName = EnemyNameList[i];
		Renderer_->CreateFolderAnimationTimeKey(EnemyName + "_WalkLeft.bmp", EnemyName + "_WalkLeft", static_cast<int>(TIME_GROUP::MONSTER), 0, 3, 0.2f, true);
		Renderer_->CreateFolderAnimationTimeKey(EnemyName + "_WalkRight.bmp", EnemyName + "_WalkRight", static_cast<int>(TIME_GROUP::MONSTER), 0, 3, 0.2f, true);
		Renderer_->CreateFolderAnimationTimeKey(EnemyName + "_Dead.bmp", EnemyName + "_Dead", static_cast<int>(TIME_GROUP::MONSTER), 0, 29, 0.1f, false);
	}
}