#pragma once

// Ό³Έν :
class VampireSurvivorsGame
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

protected:

private:

};

