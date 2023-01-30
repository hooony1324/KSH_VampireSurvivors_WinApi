#pragma once
#include <GameEngine/GameEngineActor.h>

#include <vector>

// Ό³Έν :
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

	void SkillCheck();

protected:

	void Start() override;
	void Update() override;
	void Render() override;

private:
	

private:

	std::vector<GameEngineRenderer*> ActiveSlots_;
	size_t ActiveCount_;
	std::vector<GameEngineRenderer*> PassiveSlots_;
	size_t PassiveCount_;

};

