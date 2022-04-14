#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class GameEngineCollision;
class Coin : public GameEngineActor
{
public:
	// constrcuter destructer
	Coin();
	~Coin();

	// delete Function
	Coin(const Coin& _Other) = delete;
	Coin(Coin&& _Other) noexcept = delete;
	Coin& operator=(const Coin& _Other) = delete;
	Coin& operator=(Coin&& _Other) noexcept = delete;

protected:

	void Start() override;
	void Update() override;
	void Render() override;

private:
	GameEngineCollision* Col_;
};

