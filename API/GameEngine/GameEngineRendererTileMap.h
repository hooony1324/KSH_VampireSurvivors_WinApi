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

// 설명 : 제한이 있는 타일맵을 이야기.
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
			MsgBoxAssert("0개인 타일맵을 만들수 없습니다.");
			return;
		}

		if (0 >= _Y)
		{
			MsgBoxAssert("0개인 타일맵을 만들수 없습니다.");
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
			MsgBoxAssert("0 이하의 인덱스는 존재할수 없습니다.");
		}

		if (0 > _Y)
		{
			MsgBoxAssert("0 이하의 인덱스는 존재할수 없습니다.");
		}

		if (_Y >= Tiles_.size())
		{
			MsgBoxAssert("범위를 넘길수 없습니다.");
		}

		if (_X >= Tiles_[0].size())
		{
			MsgBoxAssert("범위를 넘길수 없습니다.");
		}

		return Tiles_[_Y][_X];
	}

	bool IsTile(int _X, int _Y)
	{
		return GetTile(_X, _Y) == nullptr;
	}

	GameEngineRenderer* CreateTile(const float4& _Pos, const std::string& _Image, int _Order = static_cast<int>(EngineMax::RENDERORDERMAX));

	// 타일이미지가 1장1장 있을때
	GameEngineRenderer* CreateTile(int _X, int _Y, const std::string& _Image, int _Order = static_cast<int>(EngineMax::RENDERORDERMAX));

	// 타일이미지가 여러장 모여있는데 컷했을때
	GameEngineRenderer* CreateTile(int _X, int _Y, const std::string& _Image, int Index, int _Order = static_cast<int>(EngineMax::RENDERORDERMAX));
	void DeleteTile(int _X, int _Y);

	// 0,0(원점) 기준으로 위치해야하는 포지션을 
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

