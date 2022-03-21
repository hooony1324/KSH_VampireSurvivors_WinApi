#include "PlayLevel.h"
#include "Player.h"
#include "Library.h"

PlayLevel::PlayLevel() 
{
}

PlayLevel::~PlayLevel() 
{
}

// 리소스, 액터 생성, 맵 생성
void PlayLevel::Loading()
{
	CreateActor<Library>("Map_Library", 0);
	CreateActor<Player>("Player", 1);
}

// 레벨 변경시 진입
void PlayLevel::LevelChangeStart()
{
	
}

// GameEngine : CurrentLevle->LevelUpdate()
void PlayLevel::Update()
{

}


