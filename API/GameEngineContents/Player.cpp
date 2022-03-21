#include "Player.h"
#include <GameEngineBase/GameEngineWindow.h>

Player::Player() 
{
}

Player::~Player() 
{
}

void Player::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale({ 50, 50 });
}

void Player::Render()
{
	DebugRectRender();
}

