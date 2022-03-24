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

// 미리 로드해두면 좋은
void PlayLevel::Loading()
{

}

// 레벨 변경시 진입 (Title -> Play -> Result)
// 맵, 캐릭터, .. 가 선택 되면 해당하는 맵으로 액터를 생성해야 함
void PlayLevel::LevelChangeStart()
{
	CreateActor<Library>("Library", 0);
	CreateActor<Player>("Player", 1);
}

// GameEngine : CurrentLevle->LevelUpdate()
void PlayLevel::Update()
{

}


