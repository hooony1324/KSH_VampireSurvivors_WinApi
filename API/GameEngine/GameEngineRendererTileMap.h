#pragma once
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>


struct TileIndex
{
public:
	int X;
	int Y;
};

// ���� : ������ �ִ� Ÿ�ϸ��� �̾߱�.
class GameEngineImage;
class GameEngineRendererTileMap
{
	std::vector<std::vector<GameEngineRenderer*>> Tiles_;
	float4 TileSize_;
	float4 TileSizeHalf_;
	GameEngineActor* Master_;

public:
	void TileRangeSetting(int _X, int _Y, float4 _TileSize)
	{
		if (0 >= _X)
		{
			MsgBoxAssert("0���� Ÿ�ϸ��� ����� �����ϴ�.");
			return;
		}

		if (0 >= _Y)
		{
			MsgBoxAssert("0���� Ÿ�ϸ��� ����� �����ϴ�.");
			return;
		}

		Tiles_.resize(_Y);

		for (size_t y = 0; y < Tiles_.size(); y++)
		{
			Tiles_[y].resize(_X);

			for (size_t x = 0; x < Tiles_[y].size(); x++)
			{
				Tiles_[y][x] = nullptr;
			}
		}

		TileSize_ = _TileSize;
		TileSizeHalf_ = _TileSize.Half();
	}

	GameEngineRenderer* GetTile(int _X, int _Y)
	{
		if (0 > _X)
		{
			MsgBoxAssert("0 ������ �ε����� �����Ҽ� �����ϴ�.");
		}

		if (0 > _Y)
		{
			MsgBoxAssert("0 ������ �ε����� �����Ҽ� �����ϴ�.");
		}

		if (_Y >= Tiles_.size())
		{
			MsgBoxAssert("������ �ѱ�� �����ϴ�.");
		}

		if (_X >= Tiles_[0].size())
		{
			MsgBoxAssert("������ �ѱ�� �����ϴ�.");
		}

		return Tiles_[_Y][_X];
	}

	bool IsTile(int _X, int _Y)
	{
		return GetTile(_X, _Y) == nullptr;
	}

	GameEngineRenderer* CreateTile(const float4& _Pos, const std::string& _Image, int _Order = static_cast<int>(EngineMax::RENDERORDERMAX));

	// Ÿ���̹����� 1��1�� ������
	GameEngineRenderer* CreateTile(int _X, int _Y, const std::string& _Image, int _Order = static_cast<int>(EngineMax::RENDERORDERMAX));

	// Ÿ���̹����� ������ ���ִµ� ��������
	GameEngineRenderer* CreateTile(int _X, int _Y, const std::string& _Image, int Index, int _Order = static_cast<int>(EngineMax::RENDERORDERMAX));
	void DeleteTile(int _X, int _Y);

	// 0,0(����) �������� ��ġ�ؾ��ϴ� �������� 
	float4 GetWorldPostion(int _X, int _Y);
	TileIndex GetTileIndex(const float4& _Pos);

public:
	GameEngineRendererTileMap(GameEngineActor* _Actor)
		: Master_(_Actor)
	{
	}

	virtual ~GameEngineRendererTileMap()
	{
	}
};

