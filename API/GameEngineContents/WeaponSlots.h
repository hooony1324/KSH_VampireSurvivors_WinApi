#pragma once
#include <GameEngine/GameEngineActor.h>

// ���� :
class GameEngineRenderer;
class WeaponSlots : public GameEngineActor
{
public:
	// constrcuter destructer
	WeaponSlots();
	~WeaponSlots();

	// delete Function
	WeaponSlots(const WeaponSlots& _Other) = delete;
	WeaponSlots(WeaponSlots&& _Other) noexcept = delete;
	WeaponSlots& operator=(const WeaponSlots& _Other) = delete;
	WeaponSlots& operator=(WeaponSlots&& _Other) noexcept = delete;

protected:

	void Start() override;
	void Update() override;
	void Render() override;

private:
	void SkillCheck();

private:

	std::vector<GameEngineRenderer*> ActiveSlots_;
	size_t ActiveCount_;
	std::vector<GameEngineRenderer*> PassiveSlots_;
	size_t PassiveCount_;

};

