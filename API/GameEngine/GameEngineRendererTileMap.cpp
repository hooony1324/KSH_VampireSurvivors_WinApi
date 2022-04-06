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

GameEngineRenderer* GameEngineRendererTileMap::CreateTile(const float4& _Pos, const std::string& _Image, int _Order)
{
	TileIndex Index = GetTileIndex(_Pos);
	return CreateTile(Index.X, Index.Y, _Image);
}

GameEngineRenderer* GameEngineRendererTileMap::CreateTile(int _X, int _Y, const std::string& _Image, int _Order)
{
	GameEngineRenderer* Renderer = GetTile(_X, _Y);
	if (nullptr == Renderer)
	{
		Renderer = Master_->CreateRenderer(_Image, _Order);
	}
	else {
		Renderer->SetImage(_Image);
	}
	Renderer->SetPivot(GetWorldPostion(_X, _Y));

	Tiles_[_Y][_X] = Renderer;

	return Renderer;
}

GameEngineRenderer* GameEngineRendererTileMap::CreateTile(int _X, int _Y, const std::string& _Image, int Index, int _Order)
{
	GameEngineRenderer* Renderer = CreateTile(_X, _Y, _Image);
	Renderer->SetIndex(Index);
	Renderer->SetPivot(GetWorldPostion(_X, _Y));
	return Renderer;
}

void GameEngineRendererTileMap::DeleteTile(int _X, int _Y)
{

}