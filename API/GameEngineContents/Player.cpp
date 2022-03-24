#include "Player.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>

Player::Player() 
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
	CreateRendererToScale("Old3_01.bmp", {52, 62}, RenderPivot::CENTER);
	CreateRendererToScale("hpbar_back.bmp", { 66, 8 }, RenderPivot::CENTER, {0, 39});
	CreateRendererToScale("hpbar.bmp", { 66, 8 }, RenderPivot::CENTER, {0, 39});


}

void Player::Update()
{
	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		SetMove(float4::LEFT /** GameEngineTime::GetDeltaTime()*/);
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		SetMove(float4::RIGHT);
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		SetMove(float4::UP);
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		SetMove(float4::DOWN);
	}
}

void Player::Render()
{

}

