#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class WeaponSystem : public GameEngineActor
{
public:
	// constrcuter destructer
	WeaponSystem();
	~WeaponSystem();

	// delete Function
	WeaponSystem(const WeaponSystem& _Other) = delete;
	WeaponSystem(WeaponSystem&& _Other) noexcept = delete;
	WeaponSystem& operator=(const WeaponSystem& _Other) = delete;
	WeaponSystem& operator=(WeaponSystem&& _Other) noexcept = delete;

protected:

	void Start() override;
	void Update() override;
	void Render() override;

private:

};

