#pragma once
#include <GameEngine/GameEngineActor.h>

// ���� :
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

	// Actor�� ������ Actor�� Collision/Renderer ���� ������ ��Ȳ�� ����
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

