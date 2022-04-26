#include "TitleLevel.h"
#include "GameEngine/GameEngine.h"
#include "GameEngineBase/GameEngineInput.h"

#include "GameEnum.h"
#include "Character.h"
#include "GameInfo.h"

#include "TitleBackGround.h"
#include "GameStartMenu.h"

TitleLevel::TitleLevel() 
{
}

TitleLevel::~TitleLevel() 
{
}

void TitleLevel::Loading()
{
	CreateActor<TitleBackGround>(static_cast<int>(ACTOR_ORDER::BACKGROUND));

	StartMenu_ = CreateActor<GameStartMenu>(static_cast<int>(ACTOR_ORDER::UI));
}

void TitleLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	// BlinkingBG -> 시작하려면 아무키나 누르세요
	// 
	

}

void TitleLevel::Update()
{

}

void TitleLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{

}
