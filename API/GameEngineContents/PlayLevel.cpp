#include "PlayLevel.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineCollision.h>

#include "PlayerInfo.h"
#include "ObjectOrder.h"

#include "ExpBar.h"
#include "WeaponSlots.h"
#include "TimerUI.h"
#include "CoinUI.h"
#include "LevelUI.h"
#include "KillCountUI.h"

#include "Player.h"
#include "Library.h"
#include "Enemy.h"
#include "Mud.h"
#include "ShadeRed.h"
#include "EnemyController.h"
#include "ProjectileShooter.h"


float MapLeftX = 700;
float MapRightX = 2940;

PlayLevel::PlayLevel()
	: Player_(nullptr)
	, Map_(nullptr)
{
}

PlayLevel::~PlayLevel() 
{
}

// 미리 로드해두면 좋은
void PlayLevel::Loading()
{

}

// 레벨 변경시 진입 (Title -> Play -> Result)
// 맵, 캐릭터, .. 가 선택 되면 해당하는 맵으로 액터를 생성해야 함
void PlayLevel::LevelChangeStart()
{	
	// 맵
	CreateMap();	

	AllEnemy_.reserve(7); // 1화면에 최대100마리정도(예상)
	for (int i = 0; i < 5; i++)
	{
		Enemy_ = CreateActor<Mud>((int)RENDER_ORDER::MONSTER, "Enemy");
		Enemy_->SetPosition(float4{1500, i*40 + 600.0f});
		AllEnemy_.push_back(Enemy_);
	}

	for (int i = 0; i < 2; i++)
	{
		Enemy_ = CreateActor<ShadeRed>((int)RENDER_ORDER::MONSTER, "Enemy");
		Enemy_->SetPosition(float4{ 1100, i * 40 + 600.0f });
		AllEnemy_.push_back(Enemy_);
	}

	Player_ = CreateActor<Player>((int)RENDER_ORDER::PLAYER, "Player");
	PlayerAttackRange_ = Player_->CreateCollision("PlayerAttackRange", { 400, 400 });

	EnemyController_ = CreateActor<EnemyController>((int)RENDER_ORDER::MONSTER, "EnemyController");

	// UI
	ExpUI_ = CreateActor<ExpBar>((int)RENDER_ORDER::UI, "UI");
	WeaponUI_ = CreateActor<WeaponSlots>((int)RENDER_ORDER::UI, "UI");
	TimerUI_ = CreateActor<TimerUI>((int)RENDER_ORDER::UI, "UI");
	CoinUI_ = CreateActor<CoinUI>((int)RENDER_ORDER::UI, "UI");
	LevelUI_ = CreateActor<LevelUI>((int)RENDER_ORDER::UI, "UI");
	KillCountUI_ = CreateActor<KillCountUI>((int)RENDER_ORDER::UI, "UI");


	// 슈터
	AllBullet_.reserve(50);
	Shooter1_ = CreateActor<ProjectileShooter>((int)RENDER_ORDER::PLAYER, "Shooter");
	Shooter1_->InitShooter(BulletType::FLAME_BLUE, 5, 0.2f, 2);


	//BgmPlayer = GameEngineSound::SoundPlayControl("bgm_elrond_library.MP3");
}

void PlayLevel::LevelChangeEnd()
{
	ExpUI_->Death();
	WeaponUI_->Death();
	TimerUI_->Death();
	CoinUI_->Death();
	LevelUI_->Death();
	KillCountUI_->Death();

	Player_->Death();
	Map_->Death();
	EnemyController_->Death();

	for (Enemy* Enemy : AllEnemy_)
	{
		Enemy->Death();
	}

	AllEnemy_.clear();
	AllBullet_.clear();
	AttackableEnemy_.clear();

	PlayerAttackRange_->Death();
	Shooter1_->Death();
}

void PlayLevel::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("ChangeLevelNext"))
	{
		GameEngine::GetInst().ChangeLevel("Result");
	}

	if (true == GameEngineInput::GetInst()->IsDown("SpaceBar"))
	{
		ShootAble_ = true;
	}


	EnemyController_->SetPosition(Player_->GetPosition());


	float4 MonsterPos = UpdateAttackableEnemey();
	if (true == ShootAble_)
	{
		Projectile* Bullet =  Shooter1_->Shooting(GameEngineTime::GetDeltaTime(), Player_->GetPosition(), MonsterPos);
		
		if (nullptr != Bullet)
		{
			AllBullet_.push_back(Bullet);
		}
	}

	InfiniteMap2();
}

void PlayLevel::CreateMap()
{
	Map_ = CreateActor<Library>((int)RENDER_ORDER::MONSTER, "Library");
	// 액터의 위치, 크기 설정
	Map_->SetPosition(float4::ZERO);
	Map_->SetScale(Map_->GetRendererScale());

}

void PlayLevel::InfiniteMap()
{
	PlayerPos_ = Player_->GetPosition();
	//640 - 4230

	float4 TeleportValue = { MapRightX - MapLeftX, 0 };
	if (PlayerPos_.x > MapLeftX && PlayerPos_.x < MapRightX)
	{
		return;
	}

	float4 TargetPos;
	if (PlayerPos_.x <= MapLeftX)
	{
		Player_->SetPosition(PlayerPos_ + TeleportValue);
		
		for (Enemy* Ptr : AllEnemy_)
		{
			if (nullptr == Ptr)
			{
				continue;
			}
			TargetPos = Ptr->GetPosition() + TeleportValue;
			Ptr->SetPosition(TargetPos);
		}
		 
		for (Projectile* Ptr : AllBullet_)
		{
			if (nullptr == Ptr)
			{
				continue;
			}
			
			TargetPos = Ptr->GetPosition() + TeleportValue;
			Ptr->SetPosition(TargetPos);
		}

		AllBullet_.clear();
		return;
	}

	if (PlayerPos_.x >= MapRightX)
	{
		Player_->SetPosition(PlayerPos_ - TeleportValue);

		for (Enemy* Ptr : AllEnemy_)
		{
			if (nullptr == Ptr)
			{
				continue;
			}
			TargetPos = Ptr->GetPosition() - TeleportValue;
			Ptr->SetPosition(TargetPos);
		}

		for (Projectile* Ptr : AllBullet_)
		{
			if (nullptr == Ptr)
			{
				continue;
			}
			TargetPos = Ptr->GetPosition() - TeleportValue;
			Ptr->SetPosition(TargetPos);
		}

		AllBullet_.clear();
		return;
	}

}

void PlayLevel::InfiniteMap2()
{
	Map_->CheckPlayerOnEnd();
}

float4 PlayLevel::UpdateAttackableEnemey()
{
	if (true == PlayerAttackRange_->CollisionResult("Monster", AttackableEnemy_, CollisionType::Rect, CollisionType::Rect))
	{
		float4 MonsterPos = AttackableEnemy_[0]->GetCollisionPos();
		AttackableEnemy_.clear();

		return MonsterPos;
	}

	return Player_->GetPosition() + float4::RIGHT;

}




