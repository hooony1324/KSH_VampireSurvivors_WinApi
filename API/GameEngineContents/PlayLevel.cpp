#include "PlayLevel.h"
#include "Player.h"
#include "Library.h"
#include <GameEngine/GameEngine.h>

enum class RENDER_ORDER
{
	BACKGROUND,
	PLAYER,
	MONSTER,
	UI,
};

PlayLevel::PlayLevel() 
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
	CreateActor<Library>((int)RENDER_ORDER::BACKGROUND);
	CreateActor<Player>((int)RENDER_ORDER::PLAYER);
}

// GameEngine : CurrentLevle->LevelUpdate()
void PlayLevel::Update()
{

}


