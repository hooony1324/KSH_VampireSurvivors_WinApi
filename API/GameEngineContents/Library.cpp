#include "Library.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

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
	// - Scale 3686 x 1844
	Map_ = CreateRenderer("LibraryMap.bmp", 0 ,RenderPivot::CENTER);
	Map_->SetScale(Map_->GetScale());
	Map_->SetPivot(Map_->GetScale().Half()); // ������ ��ġ

	// ������ å�� ��ġy : 415 1420
	MapWallTop_ = CreateCollision("MapWall", float4{ Map_->GetScale().x, 40 }, { Map_->GetScale().Half().x, 340});
	MapWallBot_ = CreateCollision("MapWall", float4{ Map_->GetScale().x, 40 }, { Map_->GetScale().Half().x, 1440 });
	
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
		BumpedPlayer_[0]->GetActor()->SetPosition(BumpedPlayer_[0]->GetActor()->GetPosition() + float4{ 0, -1 }); // ���� ���� ������� ����
		BumpedPlayer_.clear();
	}
}
