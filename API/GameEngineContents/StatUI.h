#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
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

};

