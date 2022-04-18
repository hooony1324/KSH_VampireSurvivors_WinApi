#pragma once
#include <GameEngine/GameEngineActor.h>
#include <vector>

// Ό³Έν :
class GameEngineRenderer;
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


	static bool IsActivated()
	{
		return IsActivated_;
	}

	static void SetActivate(bool _Value)
	{
		IsActivated_ = _Value;
	}

	static int CreateCount_;

protected:

	void Start() override;
	void Update() override;
	void Render() override;

private:
	static bool IsActivated_;

	std::vector<int> RandomSkills_;

	GameEngineRenderer* Renderer1_;
	GameEngineRenderer* Renderer2_;
	GameEngineRenderer* Renderer3_;
	GameEngineRenderer* Renderer4_;
};

