#pragma once
#include <GameEngine/GameEngineActor.h>
#include <vector>
#include "GameEnum.h"

// Ό³Έν :
class GameEngineRenderer;
class StatUI : public GameEngineActor
{
public:
	// constrcuter destructer
	StatUI();
	~StatUI();

	// delete Function
	StatUI(const StatUI& _Other) = delete;
	StatUI(StatUI&& _Other) noexcept = delete;
	StatUI& operator=(const StatUI& _Other) = delete;
	StatUI& operator=(StatUI&& _Other) noexcept = delete;

protected:

	void Start() override;
	void Update() override;
	void Render() override;

private:

	void SetSlotBase();
	void SlotUpdate();

	std::vector<GameEngineRenderer*> ActiveSlots_;
	std::vector<GameEngineRenderer*> ActiveSkills_;
	std::vector<GameEngineRenderer*> ActiveLevels_;

	std::vector<GameEngineRenderer*> PassiveSlots_;
	std::vector<GameEngineRenderer*> PassiveSkills_;
	std::vector<GameEngineRenderer*> PassiveLevels_;

	size_t ActiveSkillCount_;
	size_t PassiveSkillCount_;
};

