#pragma once
#include "GameEngine/GameEngine.h"

// Ό³Έν :
class VampireSurvivorsGame : public GameEngine 
{
public:
	// constrcuter destructer
	VampireSurvivorsGame();
	~VampireSurvivorsGame();

	// delete Function
	VampireSurvivorsGame(const VampireSurvivorsGame& _Other) = delete;
	VampireSurvivorsGame(VampireSurvivorsGame&& _Other) noexcept = delete;
	VampireSurvivorsGame& operator=(const VampireSurvivorsGame& _Other) = delete;
	VampireSurvivorsGame& operator=(VampireSurvivorsGame&& _Other) noexcept = delete;

	void GameInit() override;
	void GameLoop() override;
	void GameEnd() override;
	
protected:

private:
	void ResourceLoad();
};

