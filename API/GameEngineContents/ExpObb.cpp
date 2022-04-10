#include "ExpObb.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
//#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

ExpObb::ExpObb() 
{
}

ExpObb::~ExpObb() 
{
}

void ExpObb::Start()
{
	GameEngineRenderer* Renderer = CreateRenderer("GemGreen.bmp");
	SetPosition({ 500, 500 });

	Col_ = CreateCollision("ExpGemGreen", Renderer->GetScale());
}

void ExpObb::Update()
{
	// Actor Order
	// player > obb
	if (true == Col_->CollisionCheck("Player", CollisionType::Rect, CollisionType::Rect))
	{
		Death();
	}
}

