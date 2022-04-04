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
	// Library 맵 환경 설정
	Map_ = CreateActor<Library>((int)RENDER_ORDER::BACKGROUND, "Map");

	Enemy_ = CreateActor<Mud>((int)RENDER_ORDER::MONSTER, "Enemy");

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

void PlayLevel::InfiniteMap()
{
	PlayerPos_ = Player_->GetPosition();

	float MapLeftX = GameEngineWindow::GetScale().Half().x;
	float MapRightX = Map_->GetScale().x - MapLeftX - 64; // 64 -> 부드럽게 넘어가기 위함

	float4 NewPlayerPos;
	float4 EnemyPos = Enemy_->GetPosition();
	EnemyPos = { EnemyPos.x - PlayerPos_.x, EnemyPos.y };
	if (PlayerPos_.x <= MapLeftX)
	{
		NewPlayerPos = { MapRightX, PlayerPos_.y };
		Player_->SetPosition(NewPlayerPos);
		Enemy_->SetPosition({NewPlayerPos.x + EnemyPos.x, EnemyPos.y});
	}

	if (PlayerPos_.x >= MapRightX)
	{
		NewPlayerPos = { MapLeftX, PlayerPos_.y };
		Player_->SetPosition(NewPlayerPos);
		Enemy_->SetPosition({ NewPlayerPos.x + EnemyPos.x, EnemyPos.y });
	}

}


