#pragma once
#include <GameEngine/GameEngineLevel.h>

// Ό³Έν :
class ResultLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	ResultLevel();
	~ResultLevel();

	// delete Function
	ResultLevel(const ResultLevel& _Other) = delete;
	ResultLevel(ResultLevel&& _Other) noexcept = delete;
	ResultLevel& operator=(const ResultLevel& _Other) = delete;
	ResultLevel& operator=(ResultLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void LevelChangeStart() override;
	void Update() override;
	void LevelChangeEnd() override;

private:

	GameEngineActor* BG_;
	GameEngineActor* Board_;
};

