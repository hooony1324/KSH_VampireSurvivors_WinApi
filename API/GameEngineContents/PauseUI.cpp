#include "PauseUI.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngineBase/GameEngineInput.h>

#include "Arrow.h"
#include "GameEnum.h"

bool PauseUI::Activated_ = false;

PauseUI::PauseUI() 
{
}

PauseUI::~PauseUI() 
{
}

void PauseUI::Start()
{
	SetScale(GameEngineWindow::GetScale());
	SetPosition(GameEngineWindow::GetScale().Half());

	GameEngineRenderer* Renderer_ = CreateRenderer("BlackBG.bmp", (static_cast<int>(RENDER_ORDER::UI)) );
	Renderer_->SetAlpha(100);
	Renderer_->CameraEffectOff();

	float4 Scale = GameEngineWindow::GetScale();

	OptionButton_ = CreateRenderer("OptionButton.bmp", (static_cast<int>(RENDER_ORDER::UI)));
	OptionButton_->CameraEffectOff();
	OptionButton_->SetScale(OptionButton_->GetScale());
	OptionButton_->SetPivot({-135, 325 });

	GameEngineRenderer* ContinueButton_ = CreateRenderer("ContinueButton.bmp", (static_cast<int>(RENDER_ORDER::UI)));
	ContinueButton_->CameraEffectOff();
	ContinueButton_->SetScale(ContinueButton_->GetScale());
	ContinueButton_->SetPivot({ 135, 325});
	
	OptionActivated_ = false;
	CurButtonIndex_ = 1;
	Buttons_[0] = OptionButton_;
	Buttons_[1] = ContinueButton_;

	Arrow_ = GetLevel()->CreateActor<Arrow>(static_cast<int>(ACTOR_ORDER::UI));
	Arrow_->On();

	QuitButton_ = CreateRenderer("ButtonExit.bmp", static_cast<int>(RENDER_ORDER::UI));
	QuitButton_->CameraEffectOff();
	QuitButton_->SetPivot({ -135, 325 });
	QuitButton_->Off();

	NextLevelOff();

}

void PauseUI::Update()
{
	Arrow_->SetTarget(Buttons_[CurButtonIndex_]);


	if (true == GameEngineInput::GetInst()->IsDown("MoveLeft"))
	{
		if (CurButtonIndex_ == 0)
		{
			return;
		}

		CurButtonIndex_--;
		
	}

	if (true == GameEngineInput::GetInst()->IsDown("MoveRight"))
	{
		if (CurButtonIndex_ == 1)
		{
			return;
		}
		OptionActivated_ = false;
		CurButtonIndex_++;
	}

	// 계속하기 / 옵션 -> 계속하기면 Pause풀고, 옵션눌렀으면 종료 활성화
	if (true == GameEngineInput::GetInst()->IsDown("SpaceBar"))
	{
		if (0 == CurButtonIndex_ && false == OptionActivated_)
		{
			// 종료 활성화
			OptionActivated_ = true;
			CurButtonIndex_ = 1;
			return;
		}

		if (0 == CurButtonIndex_ && true == OptionActivated_)
		{

			GameEngineSound::SoundPlayOneShot("ButtonQuit.mp3", 0);
			GameEngine::GetInst().ChangeLevel("Result");
		}

		if (1 == CurButtonIndex_)
		{
			// 계속하기
			OptionActivated_ = false;
			Activated_ = false;
		}
	}

	if (true == OptionActivated_)
	{
		OptionButton_->SetImage("ButtonExit.bmp");
	}
	else
	{
		OptionButton_->SetImage("OptionButton.bmp");
	}

}

void PauseUI::Render()
{

}
