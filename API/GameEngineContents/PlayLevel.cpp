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

// 미리 로드해두면 좋은
void PlayLevel::Loading()
{

}

// 레벨 변경시 진입 (Title -> Play -> Result)
// 맵, 캐릭터, .. 가 선택 되면 해당하는 맵으로 액터를 생성해야 함
void PlayLevel::LevelChangeStart()
{
	CreateActor<Library>((int)RENDER_ORDER::BACKGROUND);
	CreateActor<Player>((int)RENDER_ORDER::PLAYER);
}

// GameEngine : CurrentLevle->LevelUpdate()
void PlayLevel::Update()
{

}


