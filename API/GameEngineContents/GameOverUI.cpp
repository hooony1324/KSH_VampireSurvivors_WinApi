#include "GameOverUI.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>


#include "GameEnum.h"
#include "Arrow.h"

GameOverUI::GameOverUI() 
{
}

GameOverUI::~GameOverUI() 
{
}

void GameOverUI::Start()
{
	NextLevelOff();

	SetScale(GameEngineWindow::GetScale());
	SetPosition(GameEngineWindow::GetScale().Half());
	GameEngineRenderer* BackGround = CreateRenderer("GameOverBG.bmp", static_cast<int>(RENDER_ORDER::UI));
	BackGround->CameraEffectOff();
	BackGround->SetAlpha(170);

	GameEngineRenderer* GameOverText = CreateRenderer("GameOverText.bmp", static_cast<int>(RENDER_ORDER::UI2));
	GameOverText->CameraEffectOff();
	GameOverText->SetPivot({ 0, -150 });

	QuitButton_ = CreateRenderer("ButtonQuit.bmp", static_cast<int>(RENDER_ORDER::UI2));
	QuitButton_->CameraEffectOff();
	QuitButton_->SetPivot({ 0, 150 });
	

	ArrowPtr_ = GetLevel()->CreateActor<Arrow>(static_cast<int>(ACTOR_ORDER::UI));

}

void GameOverUI::Update()
{
	ArrowPtr_->SetTarget(QuitButton_);
}

void GameOverUI::Render()
{
	
}
