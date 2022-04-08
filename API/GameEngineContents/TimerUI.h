#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include <vector>
#include "Timer.h"

// 설명 :

class TimerUI : public GameEngineActor
{
public:
	// constrcuter destructer
	TimerUI();
	~TimerUI();

	// delete Function
	TimerUI(const TimerUI& _Other) = delete;
	TimerUI(TimerUI&& _Other) noexcept = delete;
	TimerUI& operator=(const TimerUI& _Other) = delete;
	TimerUI& operator=(TimerUI&& _Other) noexcept = delete;

	// 레벨에서 시간을 알고 싶을 때
	inline int GetTime()
	{
		return Digit1_->GetTimeCount();
	}

protected:
	void InitNumbers();

	void Start() override;
	void Update() override;
	void Render() override;


private:
	float4 TimerUIPos_;
	Timer* Digit1_;

};

