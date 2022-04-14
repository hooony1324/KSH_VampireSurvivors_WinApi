#include "ExpGem.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
//#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GameInfo.h"


float ExpGem::RedExp_ = 100.0f; // ·£´ý°æÇèÄ¡

ExpGem::ExpGem()
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

		// ÇÃ·¹ÀÌ¾î ·¹º§ ³ô¾ÆÁö¸é È¹µæ·ü ³·¾ÆÁöµµ·Ï
		float Ratio = 1 - (GameInfo::GetPlayerInfo()->Level_ / GameInfo::GetPlayerInfo()->MaxLevel_);
		Exp_ *= Ratio;

		GameInfo::GetPlayerInfo()->CurrentExp_ += Exp_;

		Death();

		if (GameInfo::GetPlayerInfo()->CurrentExp_ >= GameInfo::GetPlayerInfo()->MaxExp_)
		{
			GameInfo::GetPlayerInfo()->Level_ += 1;

			float RestExp = GameInfo::GetPlayerInfo()->CurrentExp_ - GameInfo::GetPlayerInfo()->MaxExp_;
			GameInfo::GetPlayerInfo()->CurrentExp_ = RestExp;
		}
	}
}
