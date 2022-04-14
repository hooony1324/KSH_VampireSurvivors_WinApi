#include "Coin.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GameInfo.h"

Coin::Coin() 
{
}

Coin::~Coin() 
{
}

void Coin::Start()
{
	GameEngineRenderer* Renderer_ = CreateRenderer("CoinGold.bmp");
	SetScale(Renderer_->GetScale());

	Col_ = CreateCollision("Coin", Renderer_->GetScale());
}

void Coin::Update()
{
	if (true == Col_->CollisionCheck("Player", CollisionType::Rect, CollisionType::Rect))
	{
		GameInfo::GetPlayerInfo()->EearnedCoin_ += 100;
		Death();
	}
}

void Coin::Render()
{
}
