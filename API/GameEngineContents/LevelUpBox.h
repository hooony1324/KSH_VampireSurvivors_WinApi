#pragma once
#include <GameEngine/GameEngineActor.h>

// ȹ��� ���⳪ �нú��� ������ �÷��ִ� LevelUpUI ����
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

