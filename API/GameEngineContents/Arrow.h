#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class GameEngineRenderer;
class Arrow : public GameEngineActor
{
public:
	// constrcuter destructer
	Arrow();
	~Arrow();

	// delete Function
	Arrow(const Arrow& _Other) = delete;
	Arrow(Arrow&& _Other) noexcept = delete;
	Arrow& operator=(const Arrow& _Other) = delete;
	Arrow& operator=(Arrow&& _Other) noexcept = delete;

	void SetTarget(GameEngineRenderer* _TargetRenderer)
	{
		TargetRenderer_ = _TargetRenderer;
	}

protected:

	void Start() override;
	void Update() override;
	void Render() override;

private:
	GameEngineRenderer* TargetRenderer_;

	// ARROW
	GameEngineRenderer* ArrowR_;
	GameEngineRenderer* ArrowL_;
};

