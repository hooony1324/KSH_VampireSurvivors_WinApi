#include "CoinUI.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>

#include "GameInfo.h"

CoinUI::CoinUI() 
	: EarnedCoin_(0)
	, CoinRenderer_(nullptr)
	, BackBufferDC_(nullptr)
{
}

CoinUI::~CoinUI() 
{
}

void CoinUI::Start()
{
	SetPosition(float4{GameEngineWindow::GetScale().x - 40, 33});
	SetScale(float4{ 50, 28 });

	BackBufferDC_ = GameEngine::GetInst().BackBufferDC();

	CoinRenderer_ = CreateRenderer("CoinUI.bmp");
	CoinRenderer_->CameraEffectOff();
	CoinRenderer_->SetTransColor(RGB(0, 0, 0));
	CoinRenderer_->SetPivot({25, 16});
	
	NextLevelOff();

	TextFont_.Load("../Resources/PlayUI/KO.ttf");
}

void CoinUI::Update()
{
	EarnedCoin_ = GameInfo::GetPlayerInfo()->EearnedCoin_;
}

void CoinUI::Render()
{

	// 들여쓰기
	std::string Coin = std::to_string(EarnedCoin_);
	int StrLength = static_cast<int>(Coin.length()) - 1;
	int Space = 8 * StrLength;

	TextFont_.Draw(Coin, { GameEngineWindow::GetScale().x - 40 - Space, 37.0f }, RGB(255, 255, 255), 23, 800);
}
