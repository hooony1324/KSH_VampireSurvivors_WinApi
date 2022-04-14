#pragma once
#include <GameEngine/GameEngineActor.h>

// 획득시 무기나 패시브의 레벨을 올려주는 LevelUpUI 실행
class GameEngineCollision;
class LevelUpBox : public GameEngineActor
{
public:
	// constrcuter destructer
	LevelUpBox();
	~LevelUpBox();

	// delete Function
	LevelUpBox(const LevelUpBox& _Other) = delete;
	LevelUpBox(LevelUpBox&& _Other) noexcept = delete;
	LevelUpBox& operator=(const LevelUpBox& _Other) = delete;
	LevelUpBox& operator=(LevelUpBox&& _Other) noexcept = delete;

protected:

	void Start() override;
	void Update() override;
	void Render() override;

private:
	GameEngineCollision* Col_;

};

