#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <cmath>

// ���� :
class GameEngineActor;
class Vector2D
{
public:

	static float4 GetVector(float4 _PosA, float4 _PosB)
	{
		return _PosB - _PosA;
	}

	// �� ���� ��ġ�� ���� ��
	// A -> B�� ���͹�ȯ(ũ�� 1)
	static float4 GetDirection(float4 _PosA, float4 _PosB)
	{
		return Normalized(GetVector(_PosA, _PosB));
	}

	// ���� ������ 1ũ�� ���� ����
	static float4 Normalized(float4 _Vector)
	{
		float Ratio = 1 / static_cast<float>(sqrt((pow(_Vector.x, 2) + pow(_Vector.y, 2))));
		float4 Result = _Vector * Ratio;
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

