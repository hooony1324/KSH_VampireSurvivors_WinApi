#pragma once
#include <GameEngine/GameEngineActor.h>
#include "Arrow.h"

// Ό³Έν :
class PauseUI : public GameEngineActor
{
public:
	// constrcuter destructer
	PauseUI();
	~PauseUI();

	// delete Function
	PauseUI(const PauseUI& _Other) = delete;
	PauseUI(PauseUI&& _Other) noexcept = delete;
	PauseUI& operator=(const PauseUI& _Other) = delete;
	PauseUI& operator=(PauseUI&& _Other) noexcept = delete;

protected:

	void Start() override;
	void Update() override;
	void Render() override;

private:
	Arrow* ArrowPtr_;
	bool IsOption_;
	GameEngineRenderer* Buttons_[2];
	int CurButtonIdex_;
};

