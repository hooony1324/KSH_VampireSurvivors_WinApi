#pragma once

// ���� :
class GameEngineMath
{
private:
	// constrcuter destructer
	GameEngineMath();
	~GameEngineMath();

	// delete Function
	GameEngineMath(const GameEngineMath& _Other) = delete;
	GameEngineMath(GameEngineMath&& _Other) noexcept = delete;
	GameEngineMath& operator=(const GameEngineMath& _Other) = delete;
	GameEngineMath& operator=(GameEngineMath&& _Other) noexcept = delete;

protected:

private:

};

class float4
{
public:
	static float4 LEFT;
	static float4 RIGHT;
	static float4 UP;
	static float4 DOWN;
	static float4 ZERO;

public:
	float x;
	float y;
	float z;
	float w;

public:
	bool IsZero2D()
	{
		return x == 0.0f && y == 0.0f;
	}

public:
	int ix() const
	{
		return static_cast<int>(x);
	}

	int iy() const
	{
		return static_cast<int>(y);
	}

	int iz() const
	{
		return static_cast<int>(z);
	}

	int iw() const
	{
		return static_cast<int>(w);
	}

	int hix() const
	{
		return static_cast<int>(x * 0.5f);
	}

	int hiy() const
	{
		return static_cast<int>(y * 0.5f);
	}

	int hiz() const
	{
		return static_cast<int>(z * 0.5f);
	}

	float4 Half() const
	{
		return { x * 0.5f, y * 0.5f , z * 0.5f, 1.0f };
	}

	float4 operator-(const float4& _Other) const
	{
		return { x - _Other.x, y - _Other.y, z - _Other.z, 1.0f };
	}

	float4 operator+(const float4& _Other) const
	{
		return { x + _Other.x, y + _Other.y, z + _Other.z, 1.0f };
	}

	float4 operator*(const float _Value) const
	{
		return { x * _Value, y * _Value, z * _Value, 1.0f };
	}

	float4& operator+=(const float4& _Other)
	{
		x += _Other.x;
		y += _Other.y;
		z += _Other.z;

		return *this;
	}

	float4& operator-=(const float4& _Other)
	{
		x -= _Other.x;
		y -= _Other.y;
		z -= _Other.z;

		return *this;
	}

	// ���� �߰���
	bool operator==(const float4& _Other)
	{
		return x == _Other.x && y == _Other.y && z == _Other.z;
	}

	bool operator!=(const float4& _Other)
	{
		return x != _Other.x || y != _Other.y || z != _Other.z;
	}

public:
	float4()
		: x(0.0f), y(0.0f), z(0.0f), w(1.0f)
	{

	}

	float4(float _x, float _y)
		: x(_x), y(_y), z(0.0f), w(1.0f)
	{

	}

	float4(float _x, float _y, float _z)
		: x(_x), y(_y), z(_z), w(1.0f)
	{

	}

	float4(float _x, float _y, float _z, float _w)
		: x(_x), y(_y), z(_z), w(_w)
	{

	}
};

struct GameEngineRect
{
public:
	float4 Pos;
	float4 Scale;

public:
	int CenterLeft() const
	{
		return Pos.ix() - Scale.hix();
	}

	int CenterRight() const
	{
		return Pos.ix() + Scale.hix();
	}

	int CenterTop() const
	{
		return Pos.iy() - Scale.hiy();
	}

	int CenterBot() const
	{
		return Pos.iy() + Scale.hiy();
	}

	bool OverLap(const GameEngineRect& _Other)
	{
		if (CenterBot() < _Other.CenterTop())
		{
			return false;
		}

		if (CenterTop() > _Other.CenterBot())
		{
			return false;
		}

		if (CenterRight() < _Other.CenterLeft())
		{
			return false;
		}

		if (CenterLeft() > _Other.CenterRight())
		{
			return false;
		}

		return true;
	}

public:
	GameEngineRect(float4 _Pos, float4 _Scale)
		: Pos(_Pos)
		, Scale(_Scale)
	{

	}
};

