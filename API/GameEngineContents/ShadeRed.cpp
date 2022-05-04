#include "ShadeRed.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineSound.h>

#include "GameInfo.h"
#include "GameEnum.h"
#include "Vector2D.h"
#include "Player.h"
#include <vector>
#include "PlayerAttack.h"

float KnockBackDis = 20.0f;

ShadeRed::ShadeRed() 
{
}

ShadeRed::~ShadeRed() 
{

}

void ShadeRed::Start()
{
	NextLevelOff();

	Renderer_ = CreateRenderer(static_cast<int>(RENDER_ORDER::MONSTER));
	Renderer_->CreateFolderAnimationTimeKey("ShadeRed_WalkLeft.bmp", "WalkLeft", static_cast<int>(TIME_GROUP::MONSTER), 0, 3, 0.1f, true);
	Renderer_->CreateFolderAnimationTimeKey("ShadeRed_WalkRight.bmp", "WalkRight", static_cast<int>(TIME_GROUP::MONSTER), 0, 3, 0.1f, true);
	Renderer_->CreateFolderAnimationTimeKey("ShadeRed_Dead.bmp", "Dead", static_cast<int>(TIME_GROUP::MONSTER), 0, 29, 0.1f, true);
	Renderer_->CreateFolderAnimationTimeKey("ShadeRed_SmokeDead.bmp", "SmokeDead", static_cast<int>(TIME_GROUP::MONSTER), 0, 3, 0.1f, false);
	Renderer_->ChangeAnimation("WalkLeft");

	RedCol_ = CreateCollision("Boss", { 28, 45 });
	BombRange_ = CreateCollision("Bomb", { 100, 100 });
	ActivateRange_ = CreateCollision("ActivateRange", { 600, 600 });
	ExplodeTime_.SetCount(3.5f);
	HitCounter_.SetCount(0.3f);
	Ring_ = CreateRenderer("ShadeRed_Ring.bmp", static_cast<int>(RENDER_ORDER::MONSTER));
	Ring_->Off();
	
	Hp_ = 40.0f;
	Speed_ = 170;

	ExState_ = STATE::NONE;

	ChangeState(STATE::CHASE);
}

void ShadeRed::Update()
{
	DeltaTime_ = GameEngineTime::GetDeltaTime(static_cast<int>(TIME_GROUP::MONSTER));
	RedPos_ = GetPosition();
	PlayerPos_ = GameInfo::GetPlayerInfo()->PlayerPos_;
	DestDir_ = Vector2D::GetDirection(RedPos_, PlayerPos_);

	UpdateState();
}

void ShadeRed::UpdateState()
{
	switch (State_)
	{
	case ShadeRed::STATE::CHASE:
		ChaseUpdate();
		break;
	case ShadeRed::STATE::ALERT_CHASE:
		AlertChaseUpdate();
		break;
	case ShadeRed::STATE::HIT:
		HitUpdate();
		break;
	case ShadeRed::STATE::EXPLOSION:
		ExplosionUpdate();
		break;
	case ShadeRed::STATE::DIE:
		DieUpdate();
		break;
	default:
		break;
	}
}

void ShadeRed::ChangeState(STATE _State)
{
	if (State_ != _State)
	{
		switch (_State)
		{
		case ShadeRed::STATE::CHASE:
			break;
		case ShadeRed::STATE::ALERT_CHASE:
			break;
		case ShadeRed::STATE::HIT:
			HitStart();
			break;
		case ShadeRed::STATE::EXPLOSION:
			ExplosionStart();
			break;
		case ShadeRed::STATE::DIE:
			DieStart();
			break;
		default:
			break;
		}
	}

	ExState_ = State_;
	State_ = _State;
}

void ShadeRed::ChaseUpdate()
{

	SetMove(DestDir_ * DeltaTime_ * Speed_);

	HitCheck();

	//왼쪽 오른쪽 쳐다보기
	if (0 >= DestDir_.x)
	{
		Renderer_->ChangeAnimation("WalkLeft");
	}
	else
	{
		Renderer_->ChangeAnimation("WalkRight");
	}

	if (true == ActivateRange_->CollisionCheck("Player"))
	{
		ActivateRange_->Off();
		Ring_->On();
		GameEngineSound::SoundPlayOneShot("RedAlarm.mp3", 5);
		ChangeState(STATE::ALERT_CHASE);
	}
}

// AlertChase상태 -> DIE / EXPLOSION / HIT 상태로 변환 가능
void ShadeRed::AlertChaseUpdate()
{
	SetMove(DestDir_ * DeltaTime_ * Speed_);

	HitCheck();

	// 시간 다되면 터짐
	if (true == ExplodeTime_.Start(GameEngineTime::GetDeltaTime(static_cast<int>(TIME_GROUP::MONSTER))))
	{
		std::vector<GameEngineCollision*> PlayerCol;
		if (true == BombRange_->CollisionResult("Player", PlayerCol))
		{
			Player* PlayerPtr = dynamic_cast<Player*>(PlayerCol[0]->GetActor());
			PlayerPtr->Attacked(50.0f);
			PlayerCol.clear();
		}
		// 터지고 죽음
		Ring_->Off();
		GameEngineSound::SoundPlayOneShot("RedBlow.mp3", 0);
		ChangeState(STATE::EXPLOSION);
	}
}

void ShadeRed::HitStart()
{
	GameEngineSound::SoundPlayOneShot("EnemyHit.mp3", 0);
}

void ShadeRed::HitUpdate()
{
	if (Hp_ <= 0.0f)
	{
		ChangeState(STATE::DIE);
		return;
	}

	KnockDelta_ += DeltaTime_;
	
	float4 KnockBackVec = float4::LerpLimit(KnockBackDir_, GetPosition(), KnockDelta_);
	SetMove(KnockBackVec * DeltaTime_);

	if (true == HitCounter_.Start(GameEngineTime::GetDeltaTime(static_cast<int>(TIME_GROUP::MONSTER))))
	{
		KnockDelta_ = 0;
		HitEnd();
	}

}

void ShadeRed::HitEnd()
{
	if (ExState_ == STATE::CHASE)
	{
		ChangeState(STATE::CHASE);
	}
	else if (ExState_ == STATE::ALERT_CHASE)
	{
		ChangeState(STATE::ALERT_CHASE);
	}
}

void ShadeRed::ExplosionStart()
{
	Renderer_->ChangeAnimation("SmokeDead");
	RedCol_->Off();
}

void ShadeRed::ExplosionUpdate()
{
	if (true == Renderer_->IsEndAnimation())
	{
		DieEnd();
	}
}

void ShadeRed::DieStart()
{
	Renderer_->ChangeAnimation("Dead");
	RedCol_->Off();
	Ring_->Off();
}

void ShadeRed::DieUpdate()
{
	float Distance = 20.0f;
	SetMove(KnockBackDir_ * DeltaTime_ * Distance);
	KnockBackDir_ *= 0.65f;

	if (true == Renderer_->IsEndAnimation())
	{
		DieEnd();
	}
}

void ShadeRed::DieEnd()
{
	Death();
	GameInfo::GetPlayerInfo()->KillCount_ += 1;
}

void ShadeRed::HitCheck()
{
	// 콜리전 Result
	if (nullptr == RedCol_)
	{
		return;
	}

	// 공격 충돌체크
	std::vector<GameEngineCollision*> PlayerAttacks;
	if (true == RedCol_->CollisionResult("PlayerAttack", PlayerAttacks))
	{
		PlayerAttack* Attack = dynamic_cast<PlayerAttack*>(PlayerAttacks[0]->GetActor());
		if (true == Attack->IsBullet())
		{
			// 원거리 공격이면 총알 없애야됨
			Attack->Death();
		}
		KnockBackDir_ = RedPos_ - Attack->GetPosition();
		KnockBackDir_.Normal2D();
		KnockBackDir_ *= 
		Hp_ -= Attack->GetDamage();
		PlayerAttacks.clear();

		ChangeState(STATE::HIT);
	}
}
