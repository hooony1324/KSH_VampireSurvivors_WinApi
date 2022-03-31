#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class WeaponInventory : public GameEngineActor
{
public:
	// constrcuter destructer
	WeaponInventory();
	~WeaponInventory();

	// delete Function
	WeaponInventory(const WeaponInventory& _Other) = delete;
	WeaponInventory(WeaponInventory&& _Other) noexcept = delete;
	WeaponInventory& operator=(const WeaponInventory& _Other) = delete;
	WeaponInventory& operator=(WeaponInventory&& _Other) noexcept = delete;

protected:

	void Start() override;
	void Update() override;
	void Render() override;

private:

};

