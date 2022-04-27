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

	ButtonConfirm_ = CreateRenderer("ButtonComplete.bmp", static_cast<int>(RENDER_ORDER::UI));

	ButtonConfirm_->SetPivot({ 0, 350 });
	ButtonConfirm_->On();

	ArrowPtr_ = GetLevel()->CreateActor<Arrow>(static_cast<int>(ACTOR_ORDER::UI));


}

void ResultBoard::Update()
{
	ArrowPtr_->SetTarget(ButtonConfirm_);
}

void ResultBoard::Render()
{

}
