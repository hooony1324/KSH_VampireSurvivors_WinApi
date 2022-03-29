#include "PlayLevel.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineInput.h>
#include "Player.h"
#include "Library.h"
#include "Mud.h"

#include "Enemy.h"
#include "PlayerInfo.h"


enum class RENDER_ORDER
{
	BACKGROUND,
	PLAYER,
	MONSTER,
	UI,
};

PlayLevel::PlayLevel()
	: Player_(nullptr)
{
}

PlayLevel::~PlayLevel() 
{
}

// �̸� �ε��صθ� ����
void PlayLevel::Loading()
{
	Player_ = CreateActor<Player>((int)RENDER_ORDER::PLAYER, "Player");

	// Library �� ȯ�� ����
	CreateActor<Library>((int)RENDER_ORDER::BACKGROUND);
	CreateActor<Mud>((int)RENDER_ORDER::MONSTER);
	
}

// ���� ����� ���� (Title -> Play -> Result)
// ��, ĳ����, .. �� ���� �Ǹ� �ش��ϴ� ������ ���͸� �����ؾ� ��
void PlayLevel::LevelChangeStart()
{

	

}

// GameEngine : CurrentLevle->LevelUpdate()
void PlayLevel::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("ChangeLevelNext"))
	{
		GameEngine::GlobalEngine().ChangeLevel("Result");
	}
}

void PlayLevel::LevelChangeEnd()
{
	
}


