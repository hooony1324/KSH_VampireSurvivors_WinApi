#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class GameStartButton : public GameEngineActor
{
public:
	// constrcuter destructer
	GameStartButton();
	~GameStartButton();

	// delete Function
	GameStartButton(const GameStartButton& _Other) = delete;
	GameStartButton(GameStartButton&& _Other) noexcept = delete;
	GameStartButton& operator=(const GameStartButton& _Other) = delete;
	GameStartButton& operator=(GameStartButton&& _Other) noexcept = delete;

protected:

	void Start() override;
	void Update() override;

private:

};

