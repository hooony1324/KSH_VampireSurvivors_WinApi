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

	// ImageManager�� �̸� Load�� �Ǿ� �־��(GameInit->ResourceLoad) Renderer�� ������ �� �ִ�
	CreateRenderer("Old_idle.bmp"); 
}

void Player::Render()
{

}

