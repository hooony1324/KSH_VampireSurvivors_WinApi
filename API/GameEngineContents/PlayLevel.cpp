#include "PlayLevel.h"
#include "Player.h"
#include "Library.h"

PlayLevel::PlayLevel() 
{
}

PlayLevel::~PlayLevel() 
{
}

// ���ҽ�, ���� ����, �� ����
void PlayLevel::Loading()
{
	CreateActor<Library>("Map_Library", 0);
	CreateActor<Player>("Player", 1);
}

// ���� ����� ����
void PlayLevel::LevelChangeStart()
{
	
}

// GameEngine : CurrentLevle->LevelUpdate()
void PlayLevel::Update()
{

}


