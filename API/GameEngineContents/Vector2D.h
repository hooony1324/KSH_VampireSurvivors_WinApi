#pragma once
#include <GameEngineBase/GameEngineMath.h>

// 설명 :
class GameEngineActor;
class Vector2D
{
public:

	static float4 GetVector(float4 _PosA, float4 _PosB)
	{
		return _PosB - _PosA;
	}

	static float4 GetDirection(float4 _PosA, float4 _PosB)
	{
		float4 Result = GetVector(_PosA, _PosB);
		Result.Normal2D();
		return Result;
	}

	// 벡터 -> 각도 반환
	static float NormalizedDirToDegree(float4 _Vector)
	{
		// float4::RIGHT가 기준
		float Degree = static_cast<float>(acos(_Vector.x * float4::RIGHT.x + _Vector.y * float4::RIGHT.y) * GameEngineMath::RadianToDegree);
		if (_Vector.y < 0.0f)
		{
			Degree = 360.0f - Degree;
		}
		return Degree;
	}

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

