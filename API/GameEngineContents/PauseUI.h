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
	
	static bool Activated_;
protected:

	void Start() override;
	void Update() override;
	void Render() override;

private:
	bool OptionActivated_;
	GameEngineRenderer* Buttons_[2];
	int CurButtonIndex_;

	Arrow* Arrow_;

	GameEngineRenderer* OptionButton_;
	GameEngineRenderer* QuitButton_;

};

