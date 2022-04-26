#pragma once
#include <GameEngine/GameEngineActor.h>
#include <vector>
#include "Counter.h"
#include "GameInfo.h"

struct ButtonPos
{
	int y = 0;
	int x = 0;

	bool operator==(const ButtonPos& _Other)
	{
		return y == _Other.y && x == _Other.x;
	}
};

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
	void ButtonsEnd();

	bool SetNextButton(int _y, int _x);

	// SELECT_CHARACTER
	void SelectCharacterStart();
	void SelectCharacterUpdate();
	void SelectCharacterEnd();

	// SELECT_MAP
	void SelectMapStart();
	void SelectMapUpdate();
	void SelectMapEnd();

private:
	STATE CurState_;

	// ANYKEY
	GameEngineRenderer* PressAnyKey_;
	bool AnyKeyActivated_;
	bool BlinkOn_;
	Counter BlinkCounter_;

	// ARROW
	GameEngineRenderer* ArrowR_;
	GameEngineRenderer* ArrowL_;

	// START
	//std::vector<std::vector<GameEngineRenderer*>> Buttons_;
	GameEngineRenderer* ButtonStart_;
	GameEngineRenderer* ButtonPowerUp_;
	GameEngineRenderer* ButtonChallenge_;
	GameEngineRenderer* ButtonCollection_;
	GameEngineRenderer* ButtonCrew_;
	
	
	// SELECT_CHARACTER
	//std::vector<std::vector<GameEngineRenderer*>> Characters_;
	GameEngineRenderer* CharacterSelectUI_;
	GameEngineRenderer* CharacterImelda_;
	GameEngineRenderer* CharacterCavallo_;
	GameEngineRenderer* CharacterPoe_;
	GameEngineRenderer* Characters_[static_cast<int>(CharacterType::MAX)];
	

};

