#include "Timer.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
//#include <GameEngineBase/GameEngineDebug.h>

#include <GameEngine/GameEngineRenderer.h>
#include "ObjectOrder.h"

Timer::Timer() 
	: NumberIndex_(0)
{
}

Timer::~Timer() 
{
}

void Timer::Start()
{
	// Numbers_
	Numbers_.reserve(10);
	for (std::string Num : {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"})
	{
		GameEngineRenderer* Ptr = CreateRenderer(Num + ".bmp", static_cast<int>(RENDER_ORDER::UI));
		Ptr->SetScale({ 25, 30 });
		Ptr->CameraEffectOff();
		Ptr->Off();
		Numbers_.push_back(Ptr);
	}

	Numbers_[0]->On(); // 00 : 00 최초상태

}

void Timer::Update()
{
	UpdateTimeCount();

}

void Timer::Render()
{
	NumberRender();
}

void Timer::UpdateTimeCount()
{
	DeltaTimeCount_ += GameEngineTime::GetDeltaTime();
	if (1.0f > DeltaTimeCount_)
	{
		TimeCount_ += 1;
		DeltaTimeCount_ = 0;
	}
}

void Timer::SetNumberNext()
{
	Numbers_[NumberIndex_++]->Off();

	if (EndNumberIndex_ < NumberIndex_)
	{
		NumberIndex_ = 0;
	}

	Numbers_[NumberIndex_]->On();
}

void Timer::SetTimer(float _CycleTime, int _EndNumberIndex)
{
	//   0       0    :     0	   0
	// 3600초 |  60초  |   10초  |  1초		업데이트주기
	//	0-9		0-9		   0-6		0-9		숫자

	EndNumberIndex_ = _EndNumberIndex;
	CycleTime_ = _CycleTime;
	CycleTimeCounter_ = CycleTime_;
}

void Timer::NumberRender()
{
	// 1초가 지났을 때 실행되야됨
	CycleTimeCounter_ -= GameEngineTime::GetDeltaTime();

	if (CycleTimeCounter_ > 0)
	{
		return;
	}

	SetNumberNext();
	CycleTimeCounter_ = CycleTime_;
}
