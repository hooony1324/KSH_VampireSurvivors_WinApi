#pragma once
#include "GameEngineBase/GameEngineNameObject.h"

// Ό³Έν :
class GameEngine;
class GameEngineLevel : public GameEngineNameObject
{
	friend GameEngine;
public:
	// constrcuter destructer
	GameEngineLevel();
	
	virtual ~GameEngineLevel();

	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

protected:
	virtual void Loading() = 0;

	virtual void Update() = 0;

private:
	template<typename ActorType>
	ActorType* CreateActor(const std::string& _Name)
	{
		return nullptr;
	}
};

