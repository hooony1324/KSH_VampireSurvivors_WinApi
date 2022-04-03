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
		MsgBoxAssert("�÷��̾ ���õ��� �ʾҽ��ϴ�");
	}

	// �׽�Ʈ��
	if (true == GameEngineInput::GetInst()->IsDown("ChangeLevelNext"))
	{
		// LevelChangeEnd���� �ݶ��̴��� ���� ���ʹ� �ݶ��̴�->���� ������ Death���־�� ��
		GameEngine::GetInst().ChangeLevel("Result");
	}

	InfiniteMap();

}

void PlayLevel::LevelChangeEnd()
{
	// �ݶ��̴� ����
	Player_->KillPlayer(); // �ݶ��̴� Death -> ���� Death
	Enemy_->KillEnemy();

	// �ݶ��̴� ����
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
	float MapRightX = Map_->GetScale().x - MapLeftX - 64; // 64 -> �ε巴�� �Ѿ�� ����

	if (PlayerPos_.x <= MapLeftX)
	{
		Player_->SetPosition({ MapRightX, PlayerPos_.y });
	}

	if (PlayerPos_.x >= MapRightX)
	{
		Player_->SetPosition({ MapLeftX, PlayerPos_.y });
	}

}


