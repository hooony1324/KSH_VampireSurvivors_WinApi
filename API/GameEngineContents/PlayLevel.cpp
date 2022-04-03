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

	Enemy_ = CreateActor<Mud>((int)RENDER_ORDER::MONSTER, "Enemies");

	Player_ = CreateActor<Player>((int)RENDER_ORDER::PLAYER, "Player");
	

	ExpUI_ = CreateActor<ExpBar>((int)RENDER_ORDER::UI);
	WeaponUI_ = CreateActor<WeaponSlots>((int)RENDER_ORDER::UI);
	TimerUI_ = CreateActor<TimerUI>((int)RENDER_ORDER::UI);
	CoinUI_ = CreateActor<CoinUI>((int)RENDER_ORDER::UI);
	LevelUI_ = CreateActor<LevelUI>((int)RENDER_ORDER::UI);
	KillCountUI_ = CreateActor<KillCountUI>((int)RENDER_ORDER::UI);


}

void PlayLevel::Update()
{
	if (nullptr == Player_)
	{
		MsgBoxAssert("플레이어가 선택되지 않았습니다");
	}

	// 테스트용
	if (true == GameEngineInput::GetInst()->IsDown("ChangeLevelNext"))
	{
		// LevelChangeEnd에서 콜라이더를 쓰는 액터는 콜라이더->액터 순으로 Death해주어야 함
		GameEngine::GetInst().ChangeLevel("Result");
	}

	InfiniteMap();

}

void PlayLevel::LevelChangeEnd()
{
	// 콜라이더 있음
	Player_->KillPlayer(); // 콜라이더 Death -> 액터 Death
	Enemy_->KillEnemy();

	// 콜라이더 없음
	Map_->Death();

	ExpUI_->Death();
	WeaponUI_->Death();
	TimerUI_->Death();
	CoinUI_->Death();
	LevelUI_->Death();
	KillCountUI_->Death();
	
}

void PlayLevel::InfiniteMap()
{
	PlayerPos_ = Player_->GetPosition();
	float MapLeftX = GameEngineWindow::GetScale().Half().x;
	float MapRightX = Map_->GetScale().x - MapLeftX - 64; // 64 -> 부드럽게 넘어가기 위함

	if (PlayerPos_.x <= MapLeftX)
	{
		Player_->SetPosition({ MapRightX, PlayerPos_.y });
	}

	if (PlayerPos_.x >= MapRightX)
	{
		Player_->SetPosition({ MapLeftX, PlayerPos_.y });
	}

}


