#pragma once
#include <GameEngine/GameEngineActor.h>

// 설명 :
class GameEngineActorSubObject : public GameEngineUpdateObject
{
	friend GameEngineActor;

public:
	// constrcuter destructer
	GameEngineActorSubObject();
	virtual ~GameEngineActorSubObject();

	// delete Function
	GameEngineActorSubObject(const GameEngineActorSubObject& _Other) = delete;
	GameEngineActorSubObject(GameEngineActorSubObject&& _Other) noexcept = delete;
	GameEngineActorSubObject& operator=(const GameEngineActorSubObject& _Other) = delete;
	GameEngineActorSubObject& operator=(GameEngineActorSubObject&& _Other) noexcept = delete;

	inline GameEngineActor* GetActor()
	{
		return Actor_;
	}

	// Actor는 있지만 Actor의 Collision/Renderer 따로 제거한 상황을 위해
	inline bool IsUpdate() override
	{

		return GameEngineUpdateObject::IsUpdate() && Actor_->IsUpdate();
	}

	inline bool IsDeath() override
	{
		return GameEngineUpdateObject::IsDeath() || Actor_->IsDeath();
	}

protected:
	inline void SetActor(GameEngineActor* _Actor)
	{
		Actor_ = _Actor;
	}
private:
	GameEngineActor* Actor_;

};

