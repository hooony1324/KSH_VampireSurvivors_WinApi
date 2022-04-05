#include "PlayLevel.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>

#include "PlayerInfo.h"
#include "ExpBar.h"
#include "WeaponSlots.h"
#include "TimerUI.h"
#include "CoinUI.h"
#include "LevelUI.h"
#include "KillCountUI.h"

#include "Player.h"
#include "Library.h"
#include "Mud.h"
#include "Enemy.h"
#include "EnemyController.h"


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
		Enemy_->SetPosition(float4{1300, i*40 + 600.0f});
		Enemies_.push_back(Enemy_);
	}

	Player_ = CreateActor<Player>((int)RENDER_ORDER::PLAYER, "Player");

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

	InfiniteMap();

	EnemyController_->SetPosition(Player_->GetPosition());


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
	float MapLeftX = 640;
	float MapRightX = 4230;

	float4 NewPlayerPos;
	float4 EnemyPos;
	if (PlayerPos_.x <= MapLeftX)
	{
		NewPlayerPos = { MapRightX, PlayerPos_.y };
		Player_->SetPosition(NewPlayerPos);
		
		for (Enemy* Ptr : Enemies_)
		{
			EnemyPos = Ptr->GetPosition() - float4{ PlayerPos_.x, 0 };  // 플레이어와 상대적인 거리(X축 만)
			Ptr->SetPosition({ NewPlayerPos.x + EnemyPos.x, EnemyPos.y });
		}
	}

	if (PlayerPos_.x >= MapRightX)
	{
		NewPlayerPos = { MapLeftX, PlayerPos_.y };
		Player_->SetPosition(NewPlayerPos);

		for (Enemy* Ptr : Enemies_)
		{
			EnemyPos = Ptr->GetPosition() - float4{ PlayerPos_.x, 0 };
			Ptr->SetPosition({ NewPlayerPos.x + EnemyPos.x, EnemyPos.y });
		}
	}

}




