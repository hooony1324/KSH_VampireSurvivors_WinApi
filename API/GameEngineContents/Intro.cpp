#include "Intro.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineSound.h>


#include "Counter.h"

Intro::Intro() 
{
}

Intro::~Intro() 
{
}


void Intro::Start()
{
	Renderer_ = CreateRenderer();
	Renderer_->SetPivot(GameEngineWindow::GetScale().Half());

	Renderer_->CreateAnimation("CautionToMain.bmp", "Caution", 0, 0, 0.1f, false);
	Renderer_->CreateAnimation("CautionToMain.bmp", "CautionToMain", 0, 72, 0.025f, false);
	Renderer_->ChangeAnimation("Caution");

	NextLevelOff();

	SpaceBarOnce_ = false;
}

void Intro::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("SpaceBar"))
	{
		if (true == SpaceBarOnce_)
		{
			return;
		}
		Renderer_->ChangeAnimation("CautionToMain");
		GameEngineSound::SoundPlayOneShot("Intro.mp3", 0);
		SpaceBarOnce_ = true;
	}
	

}

void Intro::Render()
{
}


bool Intro::IsCautionOut()
{
	bool Result = Renderer_->IsAnimationName("CautionToMain") && Renderer_->IsEndAnimation();
	return Result;
}