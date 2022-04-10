#pragma once
#include <GameEngine/GameEngineActor.h>
#include <vector>
// ���� :
// ��ü �ð��� ���
// Ÿ�̸� -> 1�ڸ� ���� 00:00 (�� 4�ڸ�)
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

