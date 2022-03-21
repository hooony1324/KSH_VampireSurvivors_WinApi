#pragma once
#include <GameEngine/GameEngineLevel.h>

// Ό³Έν :
class EndingCredit : public GameEngineLevel
{
public:
	// constrcuter destructer
	EndingCredit();
	~EndingCredit();

	// delete Function
	EndingCredit(const EndingCredit& _Other) = delete;
	EndingCredit(EndingCredit&& _Other) noexcept = delete;
	EndingCredit& operator=(const EndingCredit& _Other) = delete;
	EndingCredit& operator=(EndingCredit&& _Other) noexcept = delete;

protected:

private:
	void Loading() override;
	void Update() override;
};

