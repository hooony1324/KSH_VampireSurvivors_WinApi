#include "CoinUI.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
//#include <GameEngineBase/GameEngineDebug.h>

CoinUI::CoinUI() 
{
}

CoinUI::~CoinUI() 
{
}

void CoinUI::Start()
{
	SetPosition(float4{GameEngineWindow::GetScale().x - 25, 45});
	SetScale(float4{ 50, 28 });
}

void CoinUI::Update()
{
}

void CoinUI::Render()
{
	DebugRectRender();
}
