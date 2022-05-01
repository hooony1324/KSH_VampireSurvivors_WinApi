#pragma once
#include <GameEngine/GameEngineActor.h>
#include <vector>
#include "Counter.h"
#include "GameEnum.h"

// 설명 :
class GameEngineRenderer;
class LevelUpUI : public GameEngineActor
{
public:

	enum class STATE
	{
		NONE,
		BOXES,
		TREASURE,
		TREASURE_OPENING,
		TREASURE_END,
		HPMONEY,
	};

	static STATE State_;
	static bool GetBox_;

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
	void BoxesUpdate();

	void TreasureStart();
	void TreasureUpdate();

	void TreasureOpeningStart();
	void TreasureOpeningUpdate();

	void TreasureEndingStart();
	void TreasureEndingUpdate();

	void HpMoneyStart();
	void HpMoneyUpdate();

	void UIEnd();

private:
	static bool IsActivated_;
	GameEngineRenderer* BoxBackGround_;
	GameEngineActor* StatUI_;


	// 보물상자
	SkillType EvolveSkill_;
	GameEngineRenderer* BoxAnim_;
	GameEngineRenderer* Treasure_;
	Counter TreasureOnCounter_;
	SkillType SelectedTreasure_;

	SkillType SelectTreasure();


	// STATE : BOXES
	// Render1_ ~ Render4_ 액티브/패시브
	int SelectNum_;
	std::vector<SkillType> RandomSkills_;
	void ShowRandomSkills();
	void SelectSkillBox();
	void SelectSkill(SkillType _SkillType);

	GameEngineRenderer* Renderer1_;
	GameEngineRenderer* Renderer2_;
	GameEngineRenderer* Renderer3_;
	GameEngineRenderer* Renderer4_;

	GameEngineRenderer* Renderers_[4];


	// STATE : EVOLVE

	// STATE : HPMONEY

};

