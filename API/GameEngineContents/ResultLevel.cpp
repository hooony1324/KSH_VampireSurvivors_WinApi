#include "ResultLevel.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineSound.h>

#include "GameEnum.h"
#include "ResultBoard.h"
#include "GameInfo.h"


ResultLevel::ResultLevel() 
{

}

ResultLevel::~ResultLevel() 
{

}

void ResultLevel::Loading()
{
	InputActivateCount_.SetCount(0.5f);
}

void ResultLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	CreateActor<ResultBoard>(static_cast<int>(RENDER_ORDER::BACKGROUND), "Background");
}

void ResultLevel::Update()
{
	if (false == InputActivateCount_.Start(GameEngineTime::GetDeltaTime()))
	{
		return;
	}

	if (true == GameEngineInput::GetInst()->IsDown("SpaceBar"))
	{
		GameEngineSound::SoundPlayOneShot("ButtonQuit.mp3", 0);
		GameEngine::GetInst().ChangeLevel("Title");
	}
}

void ResultLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{

}

