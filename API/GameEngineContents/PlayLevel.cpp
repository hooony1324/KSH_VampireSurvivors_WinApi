#include "PlayLevel.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineCollision.h>

#include "ObjectEnum.h"

#include "ExpBar.h"
#include "WeaponSlots.h"
#include "TimerUI.h"
#include "CoinUI.h"
#include "LevelUI.h"
#include "KillCountUI.h"

#include "Player.h"
#include "Library.h"
#include "ExpGem.h"
#include "Enemy.h"
#include "Mud.h"
#include "ShadeRed.h"
#include "EnemyController.h"
#include "ProjectileShooter.h"

#include "GameInfo.h"

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
	// 시간 설정
	GameEngineTime::GetInst()->SetTimeScale(static_cast<int>(TIME_GROUP::MONSTER), 1.0f);
	GameEngineTime::GetInst()->SetTimeScale(static_cast<int>(TIME_GROUP::PLAYER), 1.0f);
	GameEngineTime::GetInst()->SetTimeScale(static_cast<int>(TIME_GROUP::WEAPON), 1.0f);

	// 맵
	CreateMap();	

	// 몬스터
	AllEnemy_.reserve(7); // 1화면에 최대100마리정도(예상)
	for (int i = 0; i < 5; i++)
	{
		Enemy_ = CreateActor<Mud>(static_cast<int>(RENDER_ORDER::MONSTER), "Enemy");
		Enemy_->SetPosition(float4{1500, i*40 + 600.0f});
		AllEnemy_.push_back(Enemy_);
	}

	for (int i = 0; i < 2; i++)
	{
		Enemy_ = CreateActor<ShadeRed>(static_cast<int>(RENDER_ORDER::MONSTER), "Enemy");
		Enemy_->SetPosition(float4{ 1100, i * 40 + 600.0f });
		AllEnemy_.push_back(Enemy_);
	}
	
	EnemyController_ = CreateActor<EnemyController>(static_cast<int>(RENDER_ORDER::MONSTER), "EnemyController");

	// 플레이어
	Player_ = CreateActor<Player>(static_cast<int>(RENDER_ORDER::PLAYER), "Player");
	/*PlayerAttackRange_ = Player_->CreateCollision("PlayerAttackRange", { 600, 600 });
	PlayerAttackRange_->Off(); */


	// UI
	ExpUI_ = CreateActor<ExpBar>(static_cast<int>(RENDER_ORDER::UI), "UI");
	WeaponUI_ = CreateActor<WeaponSlots>(static_cast<int>(RENDER_ORDER::UI), "UI");
	TimerUI_ = CreateActor<TimerUI>(static_cast<int>(RENDER_ORDER::UI), "UI");
	CoinUI_ = CreateActor<CoinUI>(static_cast<int>(RENDER_ORDER::UI), "UI");
	LevelUI_ = CreateActor<LevelUI>(static_cast<int>(RENDER_ORDER::UI), "UI");
	KillCountUI_ = CreateActor<KillCountUI>(static_cast<int>(RENDER_ORDER::UI), "UI");

	// 슈터
	ShootAble_ = false;
	Shooter1_ = CreateActor<ProjectileShooter>(static_cast<int>(RENDER_ORDER::PLAYER), "Shooter");
	Shooter1_->InitShooter(BulletType::FLAME_BLUE, 5, 0.2f, 2);


	//BgmPlayer = GameEngineSound::SoundPlayControl("bgm_elrond_library.MP3");

	// ExpGem
	ExpGem* FirstGem = CreateActor<ExpGem>(static_cast<int>(ACTOR_ORDER::ITEM), "ITEM");
	FirstGem->SetPosition({ 500, 500 });
	FirstGem->SetType(GemType::GREEN);
}

void PlayLevel::LevelChangeEnd()
{
	ExpUI_->Death();
	WeaponUI_->Death();
	TimerUI_->KillDigits();
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


	AttackableEnemy_.clear();
	AllEnemy_.clear();

	PlayerAttackRange_->Death();
	Shooter1_->Death();


}

void PlayLevel::Update()
{
	// Key Check
	if (true == GameEngineInput::GetInst()->IsDown("ChangeLevelNext"))
	{
		GameEngine::GetInst().ChangeLevel("Result");
	}

	if (true == GameEngineInput::GetInst()->IsDown("SpaceBar"))
	{
		ShootAble_ = true;
	}

	if (true == GameEngineInput::GetInst()->IsDown("Esc"))
	{
		if (false == GamePause_)
		{
			GamePause_ = true;
		}
		else
		{
			GamePause_ = false;
		}
	}


	GamePause();


	//ShooterUpdate();


	EnemyController_->SetPosition(Player_->GetPosition());
	InfiniteMap();
}

void PlayLevel::GamePause()
{
	if (true == GamePause_)
	{
		GameEngineTime::GetInst()->SetTimeScale(static_cast<int>(TIME_GROUP::MONSTER), 0.0f);
		GameEngineTime::GetInst()->SetTimeScale(static_cast<int>(TIME_GROUP::PLAYER), 0.0f);
		GameEngineTime::GetInst()->SetTimeScale(static_cast<int>(TIME_GROUP::WEAPON), 0.0f);
	}
	else
	{
		GameEngineTime::GetInst()->SetTimeScale(static_cast<int>(TIME_GROUP::MONSTER), 1.0f);
		GameEngineTime::GetInst()->SetTimeScale(static_cast<int>(TIME_GROUP::PLAYER), 1.0f);
		GameEngineTime::GetInst()->SetTimeScale(static_cast<int>(TIME_GROUP::WEAPON), 1.0f);
	}
}

void PlayLevel::CreateMap()
{
	Map_ = CreateActor<Library>(static_cast<int>(RENDER_ORDER::MONSTER), "Library");
	// 액터의 위치, 크기 설정
	Map_->SetPosition(float4::ZERO);
	Map_->SetScale(Map_->GetRendererScale());

}

void PlayLevel::InfiniteMap()
{
	Map_->CheckPlayerOnEnd();
}

float4 PlayLevel::GetAttackableEnemey()
{
	if (true == PlayerAttackRange_->CollisionResult("Monster", AttackableEnemy_, CollisionType::Rect, CollisionType::Rect))
	{
		float4 MonsterPos = AttackableEnemy_[0]->GetCollisionPos();
		AttackableEnemy_.clear();

		return MonsterPos;
	}

	return Player_->GetPosition() + float4::RIGHT;

}

void PlayLevel::ShooterUpdate()
{
	float4 MonsterPos = GetAttackableEnemey();
	if (true == ShootAble_)
	{
		Shooter1_->Shooting(GameEngineTime::GetDeltaTime(), Player_->GetPosition(), MonsterPos);
	}
}


