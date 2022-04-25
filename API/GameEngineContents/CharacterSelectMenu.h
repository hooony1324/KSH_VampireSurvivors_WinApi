#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class GameEngineRenderer;
class CharacterSelectMenu : public GameEngineActor
{
public:
	// constrcuter destructer
	CharacterSelectMenu();
	~CharacterSelectMenu();

	// delete Function
	CharacterSelectMenu(const CharacterSelectMenu& _Other) = delete;
	CharacterSelectMenu(CharacterSelectMenu&& _Other) noexcept = delete;
	CharacterSelectMenu& operator=(const CharacterSelectMenu& _Other) = delete;
	CharacterSelectMenu& operator=(CharacterSelectMenu&& _Other) noexcept = delete;

protected:

	void Start() override;
	void Update() override;
	void Render() override;

private:

};

