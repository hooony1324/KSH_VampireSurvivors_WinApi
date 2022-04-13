#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <cmath>

// 설명 :
class GameEngineActor;
class Vector2D
{
public:

	static float4 GetVector(float4 _PosA, float4 _PosB)
	{
		return _PosB - _PosA;
	}

	// 두 개의 위치가 있을 때
	// A -> B의 벡터반환(크기 1)
	static float4 GetDirection(float4 _PosA, float4 _PosB)
	{
		float4 Result = GetVector(_PosA, _PosB);
		Result.Normal2D();
		return Result;
	}

	static void DebugVectorRender(GameEngineActor* _Actor);

protected:

private:
	// constrcuter destructer
	Vector2D();
	~Vector2D();

	// delete Function
	Vector2D(const Vector2D& _Other) = delete;
	Vector2D(Vector2D&& _Other) noexcept = delete;
	Vector2D& operator=(const Vector2D& _Other) = delete;
	Vector2D& operator=(Vector2D&& _Other) noexcept = delete;

};

