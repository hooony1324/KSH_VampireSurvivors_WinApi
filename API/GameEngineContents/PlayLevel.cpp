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

// �̸� �ε��صθ� ����
void PlayLevel::Loading()
{

}

// ���� ����� ���� (Title -> Play -> Result)
// ��, ĳ����, .. �� ���� �Ǹ� �ش��ϴ� ������ ���͸� �����ؾ� ��
void PlayLevel::LevelChangeStart()
{	
	// Library �� ȯ�� ����
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

	// �׽�Ʈ��
	if (true == GameEngineInput::GetInst()->IsDown("ChangeLevelNext"))
	{
		// LevelChangeEnd���� �ݶ��̴��� ���� ���ʹ� �ݶ��̴�->���� ������ Death���־�� ��
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
	float MapRightX = Map_->GetScale().x - MapLeftX - 64; // 64 -> �ε巴�� �Ѿ�� ����

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


