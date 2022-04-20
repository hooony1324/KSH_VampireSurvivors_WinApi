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
	
}

void CoinUI::Update()
{
	EarnedCoin_ = GameInfo::GetPlayerInfo()->EearnedCoin_;
}

void CoinUI::Render()
{
	TCHAR Buffer[30] = "";
	sprintf_s(Buffer, "%d", EarnedCoin_);

	// 들여쓰기
	int StrLength = static_cast<int>(strlen(Buffer)) - 1; 
	int Space = 12 * StrLength;

	TextOutA(BackBufferDC_, GetPosition().ix() - Space, GetPosition().iy(), Buffer, static_cast<int>(strlen(Buffer)));
}
