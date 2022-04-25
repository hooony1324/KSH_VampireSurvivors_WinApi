#include "IntroLevel.h"

#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
//#include <GameEngineBase/GameEngineTime.h>

#include "GameEnum.h"
#include "Intro.h"

IntroLevel::IntroLevel() 
{
}

IntroLevel::~IntroLevel() 
{
}

void IntroLevel::Loading()
{
	BackGroundActor_ = CreateActor<Intro>();
}

void IntroLevel::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("SpaceBar"))
	{
		LevelChange_ = true;
	}

	if (true == LevelChange_ && true == BackGroundActor_->IsCautionOut())
	{
		GameEngine::GetInst().ChangeLevel("Title");
	}

}

void IntroLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{

}
