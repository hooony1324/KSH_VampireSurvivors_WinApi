#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class GameEngineRenderer;
class Arrow;
class GameOverUI : public GameEngineActor
{
public:
	// constrcuter destructer
	GameOverUI();
	~GameOverUI();

	// delete Function
	GameOverUI(const GameOverUI& _Other) = delete;
	GameOverUI(GameOverUI&& _Other) noexcept = delete;
	GameOverUI& operator=(const GameOverUI& _Other) = delete;
	GameOverUI& operator=(GameOverUI&& _Other) noexcept = delete;

protected:

	void Start() override;
	void Update() override;
	void Render() override;

private:
	GameEngineRenderer* QuitButton_;

	Arrow* ArrowPtr_;
};

