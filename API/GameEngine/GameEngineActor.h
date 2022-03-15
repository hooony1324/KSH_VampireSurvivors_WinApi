#pragma once

#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineMath.h>

// Ό³Έν :
class GameEngineLevel;
class GameEngineActor : public GameEngineNameObject
{
	friend GameEngineLevel;
public:
	// constrcuter destructer
	GameEngineActor();
	virtual ~GameEngineActor();

	// delete Function
	GameEngineActor(const GameEngineActor& _Other) = delete;
	GameEngineActor(GameEngineActor&& _Other) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
	GameEngineActor& operator=(GameEngineActor&& _Other) noexcept = delete;

protected:
	
	virtual void Start() = 0;
	virtual void Update() {}
	virtual void Render() {}

private:
	GameEngineLevel* Level_;
	float4 Position_;
	float4 Scale_;

	inline void SetLevel(GameEngineLevel* _Level)
	{
		Level_ = _Level;
	}

};

