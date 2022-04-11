#pragma once
#include <GameEngine/GameEngineActor.h>

// ���� :
class GameEngineRenderer;
class ExpBar : public GameEngineActor
{
public:
	// constrcuter destructer
	ExpBar();
	~ExpBar();

	// delete Function
	ExpBar(const ExpBar& _Other) = delete;
	ExpBar(ExpBar&& _Other) noexcept = delete;
	ExpBar& operator=(const ExpBar& _Other) = delete;
	ExpBar& operator=(ExpBar&& _Other) noexcept = delete;

protected:

	void Start() override;
	void Update() override;
	void Render() override;

private:
	GameEngineRenderer* BlackBar_;
	GameEngineRenderer* BlueBar_;

	void ExpBarUpdate();
};

