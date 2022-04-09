#include "Library.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

int TelePortX = 3584;

Library::Library() 
{

}

Library::~Library() 
{
}

void Library::Start()
{
	// Library_Books_x2
	// - Pos   { 0, 0 }
	// - Scale 3584 x 1680
	Map_ = CreateRenderer("LibraryMap2.bmp", 0 ,RenderPivot::CENTER);
	Map_->SetPivot(Map_->GetScale().Half()); // 렌더러 위치
	SetScale(Map_->GetScale());


	// 도서관 책장 위치y : 415 1420
	MapWallTop_ = CreateCollision("MapWall", float4{ Map_->GetScale().x, 40 }, { Map_->GetScale().Half().x, 400});
	MapWallBot_ = CreateCollision("MapWall", float4{ Map_->GetScale().x, 40 }, { Map_->GetScale().Half().x, 1250 });
	
	MapEndLeft_ = CreateCollision("MapEndLeft", float4{ 20, 890 }, float4{ 700, 840 });
	MapEndRight_ = CreateCollision("MapEndRight", float4{ 20, 890 }, float4{ Map_->GetScale().x - 700, 840 });
}

void Library::Update()
{
	PlayerBlock();


}

void Library::Render()
{

}

void Library::PlayerBlock()
{
	if (true == MapWallTop_->CollisionResult("Player", BumpedPlayer_, CollisionType::Rect, CollisionType::Rect))
	{
		BumpedPlayer_[0]->GetActor()->SetPosition(BumpedPlayer_[0]->GetActor()->GetPosition() + float4{ 0, 1 });
		BumpedPlayer_.clear();
	}

	if (true == MapWallBot_->CollisionResult("Player", BumpedPlayer_, CollisionType::Rect, CollisionType::Rect))
	{
		BumpedPlayer_[0]->GetActor()->SetPosition(BumpedPlayer_[0]->GetActor()->GetPosition() + float4{ 0, -1 }); // 위쪽 벽에 닿았으면 위로
		BumpedPlayer_.clear();
	}
}

float4 Library::GetRendererScale()
{
	return Map_->GetScale();
}

// 왼쪽으로 움직여야되면 -1, 오른쪽이면 1 반환
void Library::CheckPlayerOnEnd()
{

	if (true == MapEndLeft_->CollisionCheck("Player", CollisionType::Rect, CollisionType::Rect))
	{
		float4 Teleport(-TelePortX, 0);
		Map_->SetPivot(Map_->GetPivot() + Teleport);
		MapEndLeft_->SetPivot(MapEndLeft_->GetCollisionPos() + Teleport);
		MapEndRight_->SetPivot(MapEndRight_->GetCollisionPos() + Teleport);
		MapWallTop_->SetPivot(MapWallTop_->GetCollisionPos() + Teleport);
		MapWallBot_->SetPivot(MapWallBot_->GetCollisionPos() + Teleport);
	}

	if (true == MapEndRight_->CollisionCheck("Player", CollisionType::Rect, CollisionType::Rect))
	{
		float4 Teleport(TelePortX, 0);
		Map_->SetPivot(Map_->GetPivot() + Teleport);
		MapEndLeft_->SetPivot(MapEndLeft_->GetCollisionPos() + Teleport);
		MapEndRight_->SetPivot(MapEndRight_->GetCollisionPos() + Teleport);
		MapWallTop_->SetPivot(MapWallTop_->GetCollisionPos() + Teleport);
		MapWallBot_->SetPivot(MapWallBot_->GetCollisionPos() + Teleport);
	}
}


