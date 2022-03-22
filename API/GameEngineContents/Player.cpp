#include "Player.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineDebug.h>

Player::Player() 
{
}

Player::~Player() 
{
}

void Player::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale({ 100, 100 });

	// ImageManager에 미리 Load가 되어 있어야(GameInit->ResourceLoad) Renderer를 생성할 수 있다
	CreateRenderer("Old_idle.bmp"); 
}

void Player::Render()
{

}

