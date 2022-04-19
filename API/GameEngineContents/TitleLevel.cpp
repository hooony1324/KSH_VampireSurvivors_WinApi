#include "TitleLevel.h"
#include "TitleBackGround.h"
#include "TitleLogo.h"
#include "GameEngine/GameEngine.h"
#include "GameEngineBase/GameEngineInput.h"

#include "ObjectEnum.h"
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
	BG_ = CreateActor<TitleBackGround>(static_cast<int>(RENDER_ORDER::BACKGROUND));
	Logo_ = CreateActor<TitleLogo>(static_cast<int>(RENDER_ORDER::UI));

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
	BG_->Death();
	Logo_->Death();
	//PlayerInfo::GetInst()->ChangeCharacter(CharacterType::Cavallo);
	GameInfo::SetCharacter(CharacterType::Cavallo);
}
