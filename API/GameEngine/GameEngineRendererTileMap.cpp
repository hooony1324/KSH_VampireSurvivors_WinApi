#include "GameEngineRendererTileMap.h"

float4 GameEngineRendererTileMap::GetWorldPostion(int _X, int _Y)
{
	float4 ReturnPos = TileSize_;

	ReturnPos.x *= _X;
	ReturnPos.y *= _Y;
	ReturnPos += TileSizeHalf_;

	return ReturnPos;
}

TileIndex GameEngineRendererTileMap::GetTileIndex(const float4& _Pos)
{
	return { static_cast<int>(_Pos.x / TileSize_.x), static_cast<int>(_Pos.y / TileSize_.y) };
}






void GameEngineRendererTileMap::DeleteTile(int _X, int _Y)
{

}