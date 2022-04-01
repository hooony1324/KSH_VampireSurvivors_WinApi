#include "TitleLevel.h"
#include "TitleBackGround.h"
#include "TitleLogo.h"
#include "GameEngine/GameEngine.h"
#include "GameEngineBase/GameEngineInput.h"

#include "Character.h"
#include "PlayerInfo.h"


enum class RENDER_ORDER
{
	BACKGROUND,
	UI,
};

TitleLevel::TitleLevel() 
{
}

TitleLevel::~TitleLevel() 
{
}

void TitleLevel::Loading()
{
	CreateActor<TitleBackGround>((int)RENDER_ORDER::BACKGROUND);
	CreateActor<TitleLogo>((int)RENDER_ORDER::UI);
}

void TitleLevel::LevelChangeStart()
{

}

void TitleLevel::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("ChangeLevelNext"))
	{
		GameEngine::GetInst().ChangeLevel("Play");

	}
}

void TitleLevel::LevelChangeEnd()
{
	PlayerInfo::GetInst()->ChangeCharacter(Character::Type::Cavallo);
}
