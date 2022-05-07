#include "ExpGem.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineBase/GameEngineSound.h>

#include "GameEnum.h"
#include "GameInfo.h"
#include "LevelUpUI.h"


float ExpGem::RedExp_ = 100.0f; // 랜덤경험치

ExpGem::ExpGem()
	: Col_(nullptr)
	, Type_(GemType::BLUE)
	, Exp_(0)
	, Renderer_(nullptr)
	, Get_(false)
{
}

ExpGem::~ExpGem()
{
}

void ExpGem::SetType(GemType _Type)
{
	switch (_Type)
	{
		case GemType::GREEN:
		{
			Renderer_->SetImage("GemGreen.bmp");
			Exp_ = 130.0f;
			break;
		}

		case GemType::BLUE:
		{
			Renderer_->SetImage("GemBlue.bmp");
			Exp_ = 30.0f;
			break;
		}

		case GemType::RED:
		{
			Renderer_->SetImage("GemBlue.bmp");
			Exp_ = RedExp_;
			break;
		}
	}
}

void ExpGem::StateUpdate()
{
	switch (State_)
	{
	case ExpGem::STATE::IDLE:
		IdleUpdate();
		break;
	case ExpGem::STATE::MOVEOUT:
		MoveOutUpdate();
		break;
	case ExpGem::STATE::MOVEIN:
		MoveInUpdate();
		break;
	default:
		break;
	}
}

void ExpGem::ChangeState(STATE _State)
{
	State_ = _State;
}

void ExpGem::IdleUpdate()
{
	MoveDir_ = Pos_ - PlayerPos_;
	float MoveDis = MoveDir_.Len2D();
	if (GameInfo::GetPlayerInfo()->Magnet_ * 80.0f > MoveDis)
	{
		MoveDir_.Normal2D();
		MoveOutSpeed_ = 500.0f;
		ChangeState(STATE::MOVEOUT);
	}
}

void ExpGem::MoveOutUpdate()
{
	SetMove(MoveDir_ * DeltaTime_ * MoveOutSpeed_);
	MoveOutSpeed_ *= 0.95f;

	if (true == MoveOutCounter_.Start(DeltaTime_))
	{
		ChangeState(STATE::MOVEIN);
	}
}

void ExpGem::MoveInUpdate()
{
	MoveDir_ = PlayerPos_ - Pos_;
	MoveDir_.Normal2D();
	SetMove(MoveDir_ * DeltaTime_ * 400.0f);
	PlayerCheck();
}


void ExpGem::Start()
{
	NextLevelOff();
	Renderer_ = CreateRenderer("GemGreen.bmp");
	Col_ = CreateCollision("ExpGem", Renderer_->GetScale() + float4{15, 15});

	MoveOutCounter_.SetCount(0.3f);
	ChangeState(STATE::IDLE);
}

void ExpGem::Update()
{
	Pos_ = GetPosition();
	PlayerPos_ = GameInfo::GetPlayerInfo()->PlayerPos_;
	DeltaTime_ = GameEngineTime::GetDeltaTime(static_cast<int>(TIME_GROUP::ITEM));
	
	StateUpdate();

}

void ExpGem::PlayerCheck()
{
	if (true == Col_->CollisionCheck("Player", CollisionType::Rect, CollisionType::Rect))
	{
		GameEngineSound::SoundPlayOneShot("GetGem.mp3", 0);
		Death();

		// 플레이어 레벨 높아지면 획득률 낮아지도록
		float Ratio = 1 - static_cast<float>((GameInfo::GetPlayerInfo()->Level_ / GameInfo::GetPlayerInfo()->MaxLevel_));
		float EarnedExp = Exp_ * Ratio;

		float MaxExp = GameInfo::GetPlayerInfo()->MaxExp_;
		float CurrentExp = GameInfo::GetPlayerInfo()->CurrentExp_;
		float DemandExp = MaxExp - CurrentExp;

		if (EarnedExp < DemandExp)
		{
			GameInfo::GetPlayerInfo()->CurrentExp_ += EarnedExp;
		}
		else
		{
			
			float Total = CurrentExp + EarnedExp;
			int LevelUp = static_cast<int>(Total / MaxExp);
			float RestExp = Total - (MaxExp * LevelUp);
			
			GameInfo::GetPlayerInfo()->CurrentExp_ = RestExp;
			GameInfo::GetPlayerInfo()->Level_ += LevelUp;
			
			// 레벨업이 1레벨을 초과 할 시, 여러번 호출하기 위함
			LevelUpUI::GetBox_ = false;
			LevelUpUI::CreateCount_ = LevelUp;
		}

	}
}
