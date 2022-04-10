#pragma once
#include <GameEngine/GameEngineActor.h>
#include <vector>
// 설명 :
// 전체 시간도 재고
// 타이머 -> 1자리 숫자 00:00 (총 4자리)
// 

class GameEngineRenderer;
class Timer : public GameEngineActor
{
public:
	// constrcuter destructer
	Timer();
	~Timer();

	// delete Function
	Timer(const Timer& _Other) = delete;
	Timer(Timer&& _Other) noexcept = delete;
	Timer& operator=(const Timer& _Other) = delete;
	Timer& operator=(Timer&& _Other) noexcept = delete;

	int GetTimeCount()
	{
		return TimeCount_;
	}

	void SetTimer(float _CycleTime, int _EndNumberIndex);

protected:

	void Start() override;
	void Update() override;
	void Render() override;

	void UpdateTimeCount();
	void SetNumberNext();

	void NumberRender();

private:
	std::vector<GameEngineRenderer*> Numbers_;
	int NumberIndex_;
	int EndNumberIndex_;

	float DeltaTimeCount_;
	int TimeCount_;

	float	CycleTime_;
	float	CycleTimeCounter_;

};

