#include "ResultLevel.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineInput.h>

#include "GameEnum.h"
#include "ResultBoard.h"


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
	CreateActor<ResultBoard>(static_cast<int>(RENDER_ORDER::BACKGROUND), "Background");
}

void ResultLevel::Update()
{
	

	if (true == GameEngineInput::GetInst()->IsDown("SpaceBar"))
	{
		GameEngine::GetInst().ChangeLevel("Title");
	}
}

void ResultLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{

}

