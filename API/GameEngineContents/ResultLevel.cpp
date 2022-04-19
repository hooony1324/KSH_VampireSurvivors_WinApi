#include "ResultLevel.h"
#include "ResultBackGround.h"
#include "ResultBoard.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineInput.h>

#include "ObjectEnum.h"

ResultLevel::ResultLevel() 
{
}

ResultLevel::~ResultLevel() 
{
}

void ResultLevel::Loading()
{

}

void ResultLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	BG_ = CreateActor<ResultBackGround>();
	Board_ = CreateActor<ResultBoard>(1);
}

void ResultLevel::Update()
{
	

	if (true == GameEngineInput::GetInst()->IsDown("ChangeLevelNext"))
	{
		GameEngine::GetInst().ChangeLevel("Title");
	}
}

void ResultLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	BG_->Death();
	Board_->Death();
}

