#include "Player.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

// �Ѿ�
#include <GameEngine/GameEngineLevel.h>

#include "Character.h"

Player::Player() 
	: Speed_(200.0f)
{
	
}

Player::~Player() 
{
}

void Player::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale({ 100, 100 }); // ������ ������, �̹����� �������� �ƴ�

	// ImageManager�� �̸� Load�� �Ǿ� �־��(GameInit->ResourceLoad) Renderer�� ������ �� �ִ�
	CreateRenderer("Old.bmp");

}

void Player::Update()
{
	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		SetMove(float4::LEFT * GameEngineTime::GetDeltaTime() * Speed_);
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * Speed_);
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		SetMove(float4::UP * GameEngineTime::GetDeltaTime() * Speed_);
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_);
	}
}

void Player::Render()
{

}

void Player::SetCharacter(Character _Type)
{
	
}

