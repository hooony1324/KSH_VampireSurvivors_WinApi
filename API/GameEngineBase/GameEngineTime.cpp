#include "GameEngineTime.h"
#include <Windows.h>

GameEngineTime* GameEngineTime::Inst_ = new GameEngineTime();


GameEngineTime::GameEngineTime()
{
}

GameEngineTime::~GameEngineTime()
{
}

void GameEngineTime::Reset()
{
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&PrevCount_));
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&CurrentCount_));
	QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&SecondCount_));
	Update();
}

void GameEngineTime::Update()
{
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&CurrentCount_));
	RealDeltaTime_ = static_cast<double>(CurrentCount_) - static_cast<double>(PrevCount_) / static_cast<double>(SecondCount_);
	PrevCount_ = CurrentCount_;
	DeltaTime_ = static_cast<float>(RealDeltaTime_);
}