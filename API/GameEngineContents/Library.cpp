#include "Library.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineImageManager.h>


#include "GameEnum.h"

Library::Library() 
{

}

Library::~Library() 
{
}

void Library::Start()
{
	Map_ = CreateRenderer("LibraryMap.bmp", static_cast<int>(RENDER_ORDER::BACKGROUND), RenderPivot::CENTER);
	Map_->SetPivot(Map_->GetScale().Half()); // ·»´õ·¯ À§Ä¡
	SetScale(Map_->GetScale());

	// ¸Ê 1Ä­ °¡·Î±æÀÌ
	TelePortX_ = 3584.0f;

	MapEndLeft_ = CreateCollision("MapEndLeft", float4{ 20, 890 }, float4{ 700, 840 });
	MapEndRight_ = CreateCollision("MapEndRight", float4{ 20, 890 }, float4{ Map_->GetScale().x - 700, 840 });

	NextLevelOff();
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
		float4 Teleport(-TelePortX_, 0);
		Map_->SetPivot(Map_->GetPivot() + Teleport);
		MapEndLeft_->SetPivot(MapEndLeft_->GetCollisionPos() + Teleport);
		MapEndRight_->SetPivot(MapEndRight_->GetCollisionPos() + Teleport);
	}

	if (true == MapEndRight_->CollisionCheck("Player", CollisionType::Rect, CollisionType::Rect))
	{
		float4 Teleport(TelePortX_, 0);
		Map_->SetPivot(Map_->GetPivot() + Teleport);
		MapEndLeft_->SetPivot(MapEndLeft_->GetCollisionPos() + Teleport);
		MapEndRight_->SetPivot(MapEndRight_->GetCollisionPos() + Teleport);
	}
}


