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
#include "PlayerAttack.h"

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
	, Hitable_(true)
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

	HitCounter_.SetCount(0.2f);
	DeathCounter_.SetCount(1.0f);
	UpDownCounter_.SetCount(1.0f);

	NextLevelOff();

	// Medusa 움직임
	UpDown_ = 1;

	// 되살아날때 더 강해진다
	DeadCount_ = 0;

	ChangeState(STATE::DEAD);
}

void Enemy::Update()
{
	DeltaTime_ = GameEngineTime::GetDeltaTime(static_cast<int>(TIME_GROUP::MONSTER));
	Pos_ = GetPosition();


	UpdateState();

	if (Hp_ <= 0)
	{
		ChangeState(STATE::DIE);
	}
}

void Enemy::BlockOther()
{
	// Monster끼리 부딪히면
	// 서로 밀어냄
	if (true == Col_->CollisionResult("Enemy", Others_, CollisionType::Rect, CollisionType::Rect))
	{
		for (int i = 0; i < 3; i++)
		{
			if (i > Others_.size() - 1)
			{
				break;
			}
			float4 OtherPos = Others_[i]->GetActor()->GetPosition();
			Others_[i]->GetActor()->SetMove(Vector2D::GetDirection(Pos_, OtherPos) * GameEngineTime::GetDeltaTime(static_cast<int>(TIME_GROUP::MONSTER)) * 100.0f);
		}
		Others_.clear();
	}

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

void Enemy::SetDead()
{
	Dead_ = true;
	ChangeState(STATE::DEAD);
}

void Enemy::SetLive()
{
	Dead_ = false;
	On();
	Col_->On();
	Hp_ = static_cast<float>(10 + (DeadCount_ * 20));
	Speed_ = 80.0f;

	ChangeState(STATE::CHASE);
}


void Enemy::UpdateState()
{
	switch (State_)
	{
	case Enemy::STATE::DIE:
		DieUpdate();
		break;
	case Enemy::STATE::CHASE:
		ChaseUpdate();
		break;
	case Enemy::STATE::HIT:
		HitUpdate();
		break;
	case Enemy::STATE::DEAD:
		DeadUpdate();
		break;
	default:
		break;
	}
}

void Enemy::ChangeState(STATE _State)
{
	if (State_ != _State)
	{
		switch (_State)
		{
		case Enemy::STATE::DIE:
			DieStart();
			break;
		case Enemy::STATE::CHASE:
			break;
		case Enemy::STATE::HIT:
			HitStart();
			break;
		case Enemy::STATE::DEAD:
			DeadStart();
			break;
		default:
			break;
		}
	}

	State_ = _State;
}

void Enemy::DeadStart()
{
	Off();

	Dead_ = true;
}

void Enemy::DeadUpdate()
{

}

void Enemy::ChaseUpdate()
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

		DestDir_ = float4{ DestDir_.x, UpDown_ };
	}

	float Speed = MapColCheck(Speed_);

	SetMove(DestDir_ * DeltaTime_ * Speed);
	BlockOther();
	UpdateHeadDir();

	HitCheck();
}

void Enemy::HitStart()
{
	GameEngineSound::SoundPlayOneShot("EnemyHit.mp3", 0);
	KnockBackDis_ = 150.0f;

	if (Hp_ <= 0.0f)
	{
		ChangeState(STATE::DIE);
	}
}

void Enemy::HitUpdate()
{
	SetMove(KnockBackDir_ * DeltaTime_ * KnockBackDis_);
	KnockBackDis_ *= 0.95f;

	if (true == HitCounter_.Start(GameEngineTime::GetDeltaTime(static_cast<int>(TIME_GROUP::MONSTER))))
	{
		HitCounter_.Reset();
		HitEnd();
	}
}

void Enemy::HitEnd()
{
	ChangeState(STATE::CHASE);
}

void Enemy::DieStart()
{
	GameInfo::GetPlayerInfo()->KillCount_ += 1;
	Renderer_->ChangeAnimation(EnemyName_ + "_Dead");
	Col_->Off();
}

void Enemy::DieUpdate()
{
	SetMove(KnockBackDir_ * DeltaTime_ * 80.0f);

	if (true == Renderer_->IsEndAnimation())
	{
		ExpGem* Gem = GetLevel()->CreateActor<ExpGem>(static_cast<int>(ACTOR_ORDER::ITEM), "ExpGem");
		Gem->SetType(GemType::BLUE);
		Gem->SetPosition(Pos_);
		EnemyController::LiveEnemyNum -= 1;
		DeadCount_++;

		ChangeState(STATE::DEAD);
	}
}

void Enemy::HitCheck()
{
	if (false == IsUpdate())
	{
		return;
	}

	// 공격 충돌체크
	if (true == Col_->CollisionResult("PlayerAttack", PlayerAttack_))
	{
		PlayerAttack* Attack = dynamic_cast<PlayerAttack*>(PlayerAttack_[0]->GetActor());
		if (true == Attack->IsBullet())
		{
			// 원거리 공격이면 총알 없애야됨
			Attack->Death();
		}
		KnockBackDir_ = Pos_ - Attack->GetPosition();
		KnockBackDir_.Normal2D();
		Hp_ -= Attack->GetDamage();
		PlayerAttack_.clear();
		ChangeState(STATE::HIT);

	}

}
