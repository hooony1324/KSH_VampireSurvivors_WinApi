#pragma once
#include <GameEngine/GameEngineActor.h>
#include <vector>
#include "Counter.h"


// Ό³Έν :
class GameEngineRenderer;
class GameStartMenu : public GameEngineActor
{
	enum class STATE
	{
		NONE,
		ANYKEY,
		START,
		SELECT_CHARACTER,
		SELECT_MAP,
	};

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

	// FSM
	void StateUpdate();
	void ChangeState(STATE _State);

	// ANYKEY
	void BlinkStart();
	void BlinkUpdate();
	void BlinkEnd();

	void BlinkAnyKey();
	void RenderAnyKey();

	// START
	void ButtonsStart();
	void ButtonsUpdate();

	// SELECT_CHARACTER
	void SelectCharacterStart();
	void SelectCharacterUpdate();

	// SELECT_MAP
	void SelectMapStart();
	void SelectMapUpdate();

private:
	STATE CurState_;

	// ANYKEY
	GameEngineRenderer* PressAnyKey_;
	bool AnyKeyActivated_;
	bool BlinkOn_;
	Counter BlinkCounter_;

	// START
	GameEngineRenderer* Buttons_;

	
};

