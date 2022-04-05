#pragma once
#include <GameEngine/GameEngineActor.h>

// 설명 :
// 화면 밖에 벗어난 Enemy들을 Respawn해주는 액터
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

