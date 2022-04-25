#include "TimerUI.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
//#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngine/GameEngineRenderer.h>

#include <string>
#include "Timer.h"
#include "GameEnum.h"

TimerUI::TimerUI() 
{
}

TimerUI::~TimerUI() 
{

	
}

void TimerUI::KillDigits()
{
	Digit1_->Death();
	Digit2_->Death();
	Digit3_->Death();
	Digit4_->Death();
	Colone_->Death();
}

void TimerUI::InitNumbers()
{
	//	 0      0    :   0      0
	// Digit4 Digit3 : Digit2 Digit1
	Digit4_ = GetLevel()->CreateActor<Timer>(static_cast<int>(ACTOR_ORDER::UI), "Timer");
	Digit4_->SetTimer(3600, 9);
	Digit4_->SetScale({ 18, 30 });
	Digit4_->SetPosition(TimerUIPos_ + float4{-45, 0});

	Digit3_ = GetLevel()->CreateActor<Timer>(static_cast<int>(ACTOR_ORDER::UI), "Timer");
	Digit3_->SetTimer(60, 9);
	Digit3_->SetScale({ 18, 30 });
	Digit3_->SetPosition(TimerUIPos_ + float4{ -20, 0 });
	Digit3_->SetZero();

	Colone_ = CreateRenderer("Colone.bmp", static_cast<int>(RENDER_ORDER::UI));
	Colone_->SetScale({ 18, 30 });
	Colone_->CameraEffectOff();

	Digit2_ = GetLevel()->CreateActor<Timer>(static_cast<int>(ACTOR_ORDER::UI), "Timer");
	Digit2_->SetTimer(10, 5);
	Digit2_->SetScale({ 18, 30 });
	Digit2_->SetPosition(TimerUIPos_ + float4{ 25, 0 });
	Digit2_->SetZero();

	Digit1_ = GetLevel()->CreateActor<Timer>(static_cast<int>(ACTOR_ORDER::UI), "Timer");
	Digit1_->SetTimer(1, 9);
	Digit1_->SetScale({ 18, 30 });
	Digit1_->SetPosition(TimerUIPos_ + float4{ 50, 0 });
	Digit1_->SetZero();

}

void TimerUI::Start()
{
	TimerUIPos_ = float4{ GameEngineWindow::GetScale().Half().x , 50 };
	SetPosition(TimerUIPos_);
	SetScale({ 200, 50 });

	// Numbers 1~4 위치 정리, 타입(몇초만에 0->1로 바뀌는지)설정
	InitNumbers();

	
	NextLevelOff();
}

void TimerUI::Update()
{

}

void TimerUI::Render()
{

}
