#include "PlayLevel.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>

#include "PlayerInfo.h"
#include "ExpBar.h"
#include "WeaponSlots.h"

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
	Player_ = CreateActor<Player>((int)RENDER_ORDER::PLAYER);

	// Library 맵 환경 설정
	Map_ = CreateActor<Library>((int)RENDER_ORDER::BACKGROUND);
	CreateActor<Mud>((int)RENDER_ORDER::MONSTER);
	
	GameEngineActor* ExpUI = CreateActor<ExpBar>((int)RENDER_ORDER::UI);
	GameEngineActor* WeaponUI = CreateActor<WeaponSlots>((int)RENDER_ORDER::UI);
	
}

// 레벨 변경시 진입 (Title -> Play -> Result)
// 맵, 캐릭터, .. 가 선택 되면 해당하는 맵으로 액터를 생성해야 함
void PlayLevel::LevelChangeStart()
{	

}

// GameEngine : CurrentLevle->LevelUpdate()
void PlayLevel::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("ChangeLevelNext"))
	{
		GameEngine::GetInst().ChangeLevel("Result");
	}

	float4 PlayerPos = Player_->GetPosition();
	float MapLeftX = GameEngineWindow::GetScale().Half().x;
	float MapRightX = Map_->GetScale().x - GameEngineWindow::GetScale().Half().x - 64;
	
	if (PlayerPos.x <= MapLeftX)
	{
		Player_->SetPosition({ MapRightX, PlayerPos.y });
	}

	if (PlayerPos.x >= MapRightX)
	{
		Player_->SetPosition({ MapLeftX, PlayerPos.y});
	}

}

void PlayLevel::LevelChangeEnd()
{
	
}


