#include "Player.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

// 총알
#include <GameEngine/GameEngineLevel.h>
#include "Projectile.h"

#include "Character.h"

Player::Player() 
	: Speed_(200.0f)
	, Hp_(100)
	, Recovery_(0)
	, Guard_(0)
	, Power_(0)
	, Range_(1)
	, ShootSpeed_(1)
	, ShootNum_(1)
	, Duration_(3)
	, Luck_(0)
	, Growth_(1)
	, Greed_(1)
	, Magnet_(1)
	, Revival_(0)
	, Hp_BarRed_(nullptr)	// 체력 바
{

}

Player::~Player() 
{
}

void Player::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale({ 62, 52 }); // 액터의 스케일, 이미지의 스케일이 아님

	// ImageManager에 미리 Load가 되어 있어야(GameInit->ResourceLoad) Renderer를 생성할 수 있다
	CreateRenderer("old.bmp"); // { 62, 52 }
	CreateRenderer("hpbar_back.bmp", RenderPivot::CENTER, { 0, 40 });

	// 체력 바 설정
	Hp_BarRed_ = CreateRenderer("hpbar.bmp", RenderPivot::CENTER, { 0, 40 });
	Hp_BarSize_ = Hp_BarRed_->GetScale();
	
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

	if (true == GameEngineInput::GetInst()->IsDown("SpaceBar"))
	{
		Projectile* Ptr = GetLevel()->CreateActor<Projectile>();
		Ptr->SetPosition(GetPosition());
	}

	// 삭제해도 됨 삭제해도 됨 삭제해도 됨 삭제해도 됨 삭제해도 됨 삭제해도 됨
	if (true == GameEngineInput::GetInst()->IsDown("KillPlayer"))
	{
		KillPlayer();
	}

	if (true == GameEngineInput::GetInst()->IsDown("PlayerDamaged"))
	{
		Hp_ -= 10;
		
		float newSize = Hp_BarSize_.x * (Hp_ / 100);
		Hp_BarPivot_ = float4{ 0 - ((Hp_BarSize_.x - newSize)/2), Hp_BarRed_->GetPivot().y };
		Hp_BarRed_->SetScale(float4{ newSize, Hp_BarSize_.y });
		Hp_BarRed_->SetPivot(Hp_BarPivot_);
	}
	// ~삭제해도 됨 삭제해도 됨 삭제해도 됨 삭제해도 됨 삭제해도 됨 삭제해도 됨
}

void Player::Render()
{

}

void Player::SetCharacter(Character* _Type)
{
	
}

void Player::KillPlayer()
{
	GameEngineUpdateObject::Death();
}

