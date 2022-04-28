#include "ShadeRed.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineSound.h>

#include "GameInfo.h"
#include "LevelUpBox.h"
#include "Vector2D.h"
#include "PlayLevel.h"
#include "Projectile.h"
#include "Player.h"
#include <vector>

ShadeRed::ShadeRed() 
{
}

ShadeRed::~ShadeRed() 
{

}

void ShadeRed::Start()
{


	//Renderer_->CreateFolderAnimationTimeKey("ShadeRed_SmokeDead.bmp", "SmokeDead", static_cast<int>(TIME_GROUP::MONSTER), 0, 3, 0.1f, false);


	BombRange_ = CreateCollision("Bomb", { 80, 80 });
	ActivateRange_ = CreateCollision("ActivateRange", { 500, 500 });
	ExplodeTime_.SetCount(3.0f);
	ChangeState(STATE::CHASE);
}

void ShadeRed::Update()
{

}

void ShadeRed::UpdateState()
{
}

void ShadeRed::ChangeState(STATE _State)
{
}

// ¿µ¿ªÄ§¹ü½Ã
//if (0 == BossName_.compare("ShadeRed") && true == ActivateRange_->CollisionCheck("Player"))
//{
//	int a = 0;
//	ActivateRange_->Death();
//	GameEngineSound::SoundPlayOneShot("RedAlarm.mp3", 5);
//	ChangeState(BOSS_STATE::RED_ALARMCHASE);
//}

// Æø¹ß
//if (true == BombTime_.Start(GameEngineTime::GetDeltaTime(static_cast<int>(TIME_GROUP::MONSTER))))
//{
//	std::vector<GameEngineCollision*> PlayerCol;
//	if (true == BombRange_->CollisionResult("Player", PlayerCol))
//	{
//		Player* PlayerPtr = dynamic_cast<Player*>(PlayerCol[0]->GetActor());
//		PlayerPtr->Attacked(50.0f);
//		PlayerCol.clear();
//	}
//	// ÅÍÁö°í Á×À½
//	GameEngineSound::SoundPlayOneShot("RedBlow.mp3", 0);
//	ChangeState(BOSS_STATE::RED_DIE);
//}


//void Boss::RedDieStart()
//{
//	// Æø¹ß
//	Renderer_->ChangeAnimation("SmokeDead");
//
//	// ÆøÆÈÇü Á×À½, ¸Â¾Æ¼­ Á×´Â°Å¶ûÀº ´Ù¸¥ ºÐ±â
//	BombRange_->Death();
//	ActivateRange_->Death();
//	BombTime_.Reset();
//}

//case BOSSTYPE::SHADERED:
//	Hp_ = 100.0f;
//	Speed_ = 170.0f;
//	KnockBackRatio_ = 2.0f;
//	break;