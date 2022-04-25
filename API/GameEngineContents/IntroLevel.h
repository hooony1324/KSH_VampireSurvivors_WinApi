#pragma once
#include <GameEngine/GameEngineLevel.h>

// Ό³Έν :
class Intro;
class IntroLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	IntroLevel();
	~IntroLevel();

	// delete Function
	IntroLevel(const IntroLevel& _Other) = delete;
	IntroLevel(IntroLevel&& _Other) noexcept = delete;
	IntroLevel& operator=(const IntroLevel& _Other) = delete;
	IntroLevel& operator=(IntroLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:
	Intro* BackGroundActor_;
	bool LevelChange_;
};

