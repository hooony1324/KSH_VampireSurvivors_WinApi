#include "KillCountUI.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
//#include <GameEngineBase/GameEngineDebug.h>

KillCountUI::KillCountUI() 
{
}

KillCountUI::~KillCountUI() 
{
}

void KillCountUI::Start()
{
	SetPosition(float4{GameEngineWindow::GetScale().Half().x, 0 } + float4{410, 45});
	SetScale(float4{60, 28});
}

void KillCountUI::Update()
{
}

void KillCountUI::Render()
{
	DebugRectRender();
}
