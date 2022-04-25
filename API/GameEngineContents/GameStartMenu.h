#pragma once
#include <GameEngine/GameEngineActor.h>
#include <vector>

// Ό³Έν :
class GameEngineRenderer;
class GameStartMenu : public GameEngineActor
{
public:
	// constrcuter destructer
	GameStartMenu();
	~GameStartMenu();

	// delete Function
	GameStartMenu(const GameStartMenu& _Other) = delete;
	GameStartMenu(GameStartMenu&& _Other) noexcept = delete;
	GameStartMenu& operator=(const GameStartMenu& _Other) = delete;
	GameStartMenu& operator=(GameStartMenu&& _Other) noexcept = delete;

protected:

	void Start() override;
	void Update() override;
	void Render() override;

private:
	GameEngineRenderer* PressAnyKey_;

	std::vector<GameEngineRenderer*> Buttons_;
	//  []
	//[][][]
	//  []
};

