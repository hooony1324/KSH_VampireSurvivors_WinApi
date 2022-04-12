#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class LevelUpUI : public GameEngineActor
{
public:
	// constrcuter destructer
	LevelUpUI();
	~LevelUpUI();

	// delete Function
	LevelUpUI(const LevelUpUI& _Other) = delete;
	LevelUpUI(LevelUpUI&& _Other) noexcept = delete;
	LevelUpUI& operator=(const LevelUpUI& _Other) = delete;
	LevelUpUI& operator=(LevelUpUI&& _Other) noexcept = delete;

protected:

	void Start() override;
	void Update() override;
	void Render() override;

private:

};

