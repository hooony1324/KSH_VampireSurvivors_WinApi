#include "ExpGem.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
//#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineBase/GameEngineSound.h>

#include "ObjectEnum.h"
#include "GameInfo.h"
#include "LevelUpUI.h"


float ExpGem::RedExp_ = 100.0f; // 랜덤경험치

ExpGem::ExpGem()
	: Col_(nullptr)
	, Type_(GemType::BLUE)
	, Exp_(0)
	, Renderer_(nullptr)
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

void ExpGem::Start()
{
	Renderer_ = CreateRenderer("GemGreen.bmp");
	Col_ = CreateCollision("ExpGem", Renderer_->GetScale());
	
}

void ExpGem::Update()
{
	PlayerCheck();
}

void ExpGem::PlayerCheck()
{
	if (true == Col_->CollisionCheck("Player", CollisionType::Rect, CollisionType::Rect))
	{
		GameEngineSound::SoundPlayOneShot("GetGem.mp3", 0);
		Death();

		// 플레이어 레벨 높아지면 획득률 낮아지도록
		float Ratio = 1 - (GameInfo::GetPlayerInfo()->Level_ / GameInfo::GetPlayerInfo()->MaxLevel_);
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
			
			// 레벨 업 한만큼 UI호출
			LevelUpUI::CreateCount_ += LevelUp;
		}

	}
}
