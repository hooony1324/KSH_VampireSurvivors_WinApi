#include "ResultBoard.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngine/GameEngineRenderer.h>

#include "GameEnum.h"
#include "Arrow.h"

ResultBoard::ResultBoard() 
{
}

ResultBoard::~ResultBoard() 
{
}

void ResultBoard::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale(GameEngineWindow::GetScale());

	GameEngineRenderer* Background = CreateRenderer("ResultBoard.bmp", static_cast<int>(RENDER_ORDER::BACKGROUND));

	GameEngineRenderer* ButtonConfirm = CreateRenderer("ButtonQuit.bmp", static_cast<int>(RENDER_ORDER::UI));

	ButtonConfirm->SetPivot({ 0, 350 });
	ButtonConfirm->Off();

	ArrowPtr_ = GetLevel()->CreateActor<Arrow>(static_cast<int>(ACTOR_ORDER::UI));
	ArrowPtr_->SetTarget(ButtonConfirm);

}

void ResultBoard::Update()
{
}

void ResultBoard::Render()
{

}
