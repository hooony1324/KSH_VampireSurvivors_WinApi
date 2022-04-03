#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
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

protected:

	void Start() override;
	void Update() override;
	void Render() override;

private:

};

