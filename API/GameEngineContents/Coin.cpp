#include "Coin.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineBase/GameEngineSound.h>

#include "GameInfo.h"

Coin::Coin() 
	: Col_(nullptr)
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
		GameEngineSound::SoundPlayOneShot("GetCoin.mp3", 0);
		GameInfo::GetPlayerInfo()->EearnedCoin_ += 100;
		Death();
	}
}

void Coin::Render()
{
}
