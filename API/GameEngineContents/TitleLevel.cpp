#include "TitleLevel.h"
#include "GameEngine/GameEngine.h"
#include "GameEngineBase/GameEngineInput.h"

#include "GameEnum.h"
#include "Character.h"
#include "GameInfo.h"


TitleLevel::TitleLevel() 
{
}

TitleLevel::~TitleLevel() 
{
}

void TitleLevel::Loading()
{

}

void TitleLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	// BlinkingBG -> 시작하려면 아무키나 누르세요
	// 
	

}

void TitleLevel::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("ChangeLevelNext"))
	{
		GameEngine::GetInst().ChangeLevel("Play");

	}
}

void TitleLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{

	//PlayerInfo::GetInst()->ChangeCharacter(CharacterType::Cavallo);
	GameInfo::SetCharacter(CharacterType::Cavallo);
}
