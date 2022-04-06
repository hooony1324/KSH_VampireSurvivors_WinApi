#include "PlayLevel.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineActor.h>

#include "PlayerInfo.h"
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
#include "Projectile.h"
#include "WeaponSystem.h"

float MapLeftX = 640;
float MapRightX = 4230;


enum class RENDER_ORDER
{
	BACKGROUND,
	MONSTER,
	PLAYER,
	UI,
};

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
	CreateInfiniteMap();	

	for (int i = 0; i < 5; i++)
	{
		Enemy_ = CreateActor<Mud>((int)RENDER_ORDER::MONSTER, "Enemy");
		Enemy_->SetPosition(float4{1500, i*40 + 600.0f});
		Enemies_.push_back(Enemy_);
	}

	for (int i = 0; i < 2; i++)
	{
		Enemy_ = CreateActor<ShadeRed>((int)RENDER_ORDER::MONSTER, "Enemy");
		Enemy_->SetPosition(float4{ 1100, i * 40 + 600.0f });
		Enemies_.push_back(Enemy_);
	}

	Player_ = CreateActor<Player>((int)RENDER_ORDER::PLAYER, "Player");
	WeaponSystem_ = CreateActor<WeaponSystem>((int)RENDER_ORDER::PLAYER, "PlayerWeapon");

	EnemyController_ = CreateActor<EnemyController>((int)RENDER_ORDER::MONSTER, "EController");

	ExpUI_ = CreateActor<ExpBar>((int)RENDER_ORDER::UI, "UI");
	WeaponUI_ = CreateActor<WeaponSlots>((int)RENDER_ORDER::UI, "UI");
	TimerUI_ = CreateActor<TimerUI>((int)RENDER_ORDER::UI, "UI");
	CoinUI_ = CreateActor<CoinUI>((int)RENDER_ORDER::UI, "UI");
	LevelUI_ = CreateActor<LevelUI>((int)RENDER_ORDER::UI, "UI");
	KillCountUI_ = CreateActor<KillCountUI>((int)RENDER_ORDER::UI, "UI");

}

void PlayLevel::Update()
{

	// 테스트용
	if (true == GameEngineInput::GetInst()->IsDown("ChangeLevelNext"))
	{
		// LevelChangeEnd에서 콜라이더를 쓰는 액터는 콜라이더->액터 순으로 Death해주어야 함
		GameEngine::GetInst().ChangeLevel("Result");
	}


	if (true == GameEngineInput::GetInst()->IsDown("SpaceBar"))
	{
 		Projectile* Bullet = CreateActor<Projectile>((int)RENDER_ORDER::PLAYER, "Bullet");
		Bullet->SetPosition(Player_->GetPosition());
		Bullet->Death(5);
		Bullets_.push_back(Bullet);
	}

	InfiniteMap();

	EnemyController_->SetPosition(Player_->GetPosition());
	WeaponSystem_->SetPosition(Player_->GetPosition());

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
	Enemy_->Death();

	Map_->Death();

	EnemyController_->Death();
}

void PlayLevel::CreateInfiniteMap()
{
	Map_ = CreateActor<Library>((int)RENDER_ORDER::MONSTER, "Library");
	Map_->SetPosition(float4::ZERO);
	Map_->SetScale({ 100, 100 });
	
	
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

		for (Enemy* Ptr : Enemies_)
		{
			TargetPos = Ptr->GetPosition() + TeleportValue;
			//Ptr->SetPosition({ NewPlayerPos.x + EnemyPos.x, EnemyPos.y });
			Ptr->SetPosition(TargetPos);
		}

		for (Projectile* Ptr : Bullets_)
		{
			TargetPos = Ptr->GetPosition() + TeleportValue;
			Ptr->SetPosition(TargetPos);
		}
	}

	if (PlayerPos_.x >= MapRightX)
	{
		Player_->SetPosition(PlayerPos_ - TeleportValue);

		for (Enemy* Ptr : Enemies_)
		{
			TargetPos = Ptr->GetPosition() - TeleportValue;
			//Ptr->SetPosition({ NewPlayerPos.x + EnemyPos.x, EnemyPos.y });
			Ptr->SetPosition(TargetPos);
		}

		for (Projectile* Ptr : Bullets_)
		{
			TargetPos = Ptr->GetPosition() - TeleportValue;
			Ptr->SetPosition(TargetPos);
		}
	}

}




