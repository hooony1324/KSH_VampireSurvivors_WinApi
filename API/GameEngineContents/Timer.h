#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
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

protected:

	void Start() override;
	void Update() override;
	void Render() override;

private:

};

