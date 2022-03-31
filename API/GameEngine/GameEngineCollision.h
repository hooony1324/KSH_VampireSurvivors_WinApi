#pragma once
#include "GameEngineActorSubObject.h"
#include "GameEngineEnum.h"
#include <map>

// Ό³Έν :
class GameEngineImage;
class GameEngineCollision : public GameEngineActorSubObject
{
	friend GameEngineActor;

public:
	// constrcuter destructer
	GameEngineCollision();
	~GameEngineCollision();

	// delete Function
	GameEngineCollision(const GameEngineCollision& _Other) = delete;
	GameEngineCollision(GameEngineCollision&& _Other) noexcept = delete;
	GameEngineCollision& operator=(const GameEngineCollision& _Other) = delete;
	GameEngineCollision& operator=(GameEngineCollision&& _Other) noexcept = delete;

	inline void SetPivot(const float4& _Pos)
	{
		Pivot_ = _Pos;
	}

	inline void SetScale(const float4& _Scale)
	{
		Scale_ = _Scale;
	}

	bool CollisionCheck(
		const std::string& _TargetGroup,
		CollisionType _This = CollisionType::Circle,
		CollisionType _Target = CollisionType::Circle
	);

protected:

private:
	friend class FrameAnimation;
	float4 Pivot_;
	float4 Scale_;

};

