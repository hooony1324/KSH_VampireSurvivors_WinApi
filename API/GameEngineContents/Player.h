#pragma once
#include <GameEngine/GameEngineActor.h>

// 설명 : 
class Character;
class Player : public GameEngineActor
{
public:
	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	void SetCharacter(Character _Type);
protected:

private:
	void Start() override;
	void Update() override;
	void Render() override;

	// 기본 능력치 (체력, 스피드, 공격력, ...)
	float Speed_;



};

