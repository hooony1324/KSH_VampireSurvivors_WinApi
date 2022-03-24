#include "PlayLevel.h"
#include "Player.h"
#include "Library.h"
#include <GameEngine/GameEngine.h>

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
	CreateActor<Library>("Library", 0);
	CreateActor<Player>("Player", 1);
}

// GameEngine : CurrentLevle->LevelUpdate()
void PlayLevel::Update()
{

}


