#pragma once
#include <GameEngine/GameEngineActor.h>
#include <vector>

// 설명 :
class GameEngineRenderer;
class LevelUpUI : public GameEngineActor
{
public:

	enum class STATE
	{
		NONE,
		BOXES,
		EVOLVE,
		HPMONEY,
	};

	static STATE State_;

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
	
	// FSM


	void UpdateState();
	void ChangeState(STATE _State);

	void BoxesStart();
	void EvolveStart();
	void HpMoneyStart();

	void BoxesUpdate();
	void EvolveUpdate();
	void HpMoneyUpdate();

private:
	static bool IsActivated_;

	GameEngineActor* StatUI_;




	// STATE : BOXES
	// Render1_ ~ Render4_ 액티브/패시브
	int SelectNum_;
	std::vector<int> RandomSkills_;
	void ShowRandomSkills();
	void SelectSkillBox();
	void SelectSkill(int _SkillNumber);

	GameEngineRenderer* Renderer1_;
	GameEngineRenderer* Renderer2_;
	GameEngineRenderer* Renderer3_;
	GameEngineRenderer* Renderer4_;

	GameEngineRenderer* Renderers_[4];


	// STATE : EVOLVE

	// STATE : HPMONEY

};

