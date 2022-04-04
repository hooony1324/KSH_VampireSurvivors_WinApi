#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class EnemyController : public GameEngineActor
{
public:
	// constrcuter destructer
	EnemyController();
	~EnemyController();

	// delete Function
	EnemyController(const EnemyController& _Other) = delete;
	EnemyController(EnemyController&& _Other) noexcept = delete;
	EnemyController& operator=(const EnemyController& _Other) = delete;
	EnemyController& operator=(EnemyController&& _Other) noexcept = delete;

protected:

	void Start() override;
	void Update() override;
	void Render() override;

private:

	GameEngineCollision* EnemyCollectorL_;
	GameEngineCollision* EnemyCollectorR_;

	GameEngineCollision* EnemySpawnerL_;
	GameEngineCollision* EnemySpawnerR_;
};

