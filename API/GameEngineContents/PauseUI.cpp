#include "PauseUI.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngine/GameEngineRenderer.h>

#include <GameEngineBase/GameEngineInput.h>
#include "Arrow.h"
#include "GameEnum.h"

bool OptionActivated = false;
int CurButtonIdex = 1;


PauseUI::PauseUI() 
	:IsOption_(false)
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

	GameEngineRenderer* OptionButton_ = CreateRenderer("OptionButton.bmp", (static_cast<int>(RENDER_ORDER::UI)));
	OptionButton_->CameraEffectOff();
	OptionButton_->SetScale(OptionButton_->GetScale());
	OptionButton_->SetPivot({-135, 325 });

	GameEngineRenderer* ContinueButton_ = CreateRenderer("ContinueButton.bmp", (static_cast<int>(RENDER_ORDER::UI)));
	ContinueButton_->CameraEffectOff();
	ContinueButton_->SetScale(ContinueButton_->GetScale());
	ContinueButton_->SetPivot({ 135, 325});
	
	CurButtonIdex_ = 1;
	Buttons_[0] = OptionButton_;
	Buttons_[1] = ContinueButton_;

	NextLevelOff();

	ArrowPtr_ = GetLevel()->CreateActor<Arrow>(static_cast<int>(ACTOR_ORDER::UI));

}

void PauseUI::Update()
{
	if (true == IsUpdate())
	{
		ArrowPtr_->On();
	}
	else
	{
		ArrowPtr_->Off();
	}

	ArrowPtr_->SetTarget(Buttons_[CurButtonIdex]);


	if (true == GameEngineInput::GetInst()->IsDown("MoveLeft"))
	{
		if (CurButtonIdex == 0)
		{
			return;
		}

		CurButtonIdex--;
		
	}

	if (true == GameEngineInput::GetInst()->IsDown("MoveRight"))
	{
		if (CurButtonIdex == 1)
		{
			return;
		}

		CurButtonIdex++;
	}


	int a = 0;

}

void PauseUI::Render()
{

}
