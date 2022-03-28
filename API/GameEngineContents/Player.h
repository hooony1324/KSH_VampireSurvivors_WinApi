#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν : 
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

	void KillPlayer();

private:
	void Start() override;
	void Update() override;
	void Render() override;

private:

	GameEngineRenderer* Hp_BarRed_;
	float4				Hp_BarSize_;
	float4				Hp_BarPivot_;
};

