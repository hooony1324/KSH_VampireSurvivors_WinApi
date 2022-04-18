#include "Library.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

float TelePortX = 3584.0f;

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
	Map_ = CreateRenderer("LibraryMap.bmp", 0 ,RenderPivot::CENTER);
	Map_->SetPivot(Map_->GetScale().Half()); // ·»´õ·¯ À§Ä¡
	SetScale(Map_->GetScale());


	MapEndLeft_ = CreateCollision("MapEndLeft", float4{ 20, 890 }, float4{ 700, 840 });
	MapEndRight_ = CreateCollision("MapEndRight", float4{ 20, 890 }, float4{ Map_->GetScale().x - 700, 840 });
}

void Library::Update()
{


}

void Library::Render()
{

}

float4 Library::GetRendererScale()
{
	return Map_->GetScale();
}

void Library::CheckPlayerOnEnd()
{

	if (true == MapEndLeft_->CollisionCheck("Player", CollisionType::Rect, CollisionType::Rect))
	{
		float4 Teleport(-TelePortX, 0);
		Map_->SetPivot(Map_->GetPivot() + Teleport);
		MapEndLeft_->SetPivot(MapEndLeft_->GetCollisionPos() + Teleport);
		MapEndRight_->SetPivot(MapEndRight_->GetCollisionPos() + Teleport);
	}

	if (true == MapEndRight_->CollisionCheck("Player", CollisionType::Rect, CollisionType::Rect))
	{
		float4 Teleport(TelePortX, 0);
		Map_->SetPivot(Map_->GetPivot() + Teleport);
		MapEndLeft_->SetPivot(MapEndLeft_->GetCollisionPos() + Teleport);
		MapEndRight_->SetPivot(MapEndRight_->GetCollisionPos() + Teleport);
	}
}


