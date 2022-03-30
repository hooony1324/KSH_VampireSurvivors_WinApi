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
#include "PlayerInfo.h"

#include <GameEngine/GameEngineRenderer.h>

Player::Player() 
	: Hp_BarRed_(nullptr)	// 체력 바
	, PlayerRenderer_(nullptr)
{

}

Player::~Player() 
{
}

void Player::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale({ 100, 100 }); // 액터의 스케일, 이미지의 스케일이 아님


	PlayerInfo::GetInst()->ChangeCharacter(Character::Type::Cavallo);

	GameEngineRenderer* PlayerRenderer_ = CreateRenderer();
	PlayerRenderer_->CreateAnimation("Cavallo_WalkRight.bmp", "Idle_Right", 0, 0, 0.1f, false);
	PlayerRenderer_->CreateAnimation("Cavallo_WalkRight.bmp", "Walk_Right", 0, 3, 0.12f, true);
	PlayerRenderer_->ChangeAnimation("Idle_Right"); 

	
	CreateRenderer("hpbar_back.bmp", RenderPivot::CENTER, { 0, 40 });

	// 체력 바 설정
	Hp_BarRed_ = CreateRenderer("hpbar.bmp", RenderPivot::CENTER, { 0, 40 });
	Hp_BarSize_ = Hp_BarRed_->GetScale();
	
}

void Player::Update()
{
	Character* PlayerStat = PlayerInfo::GetInst()->Character_;
	float Speed = PlayerStat->Speed_;
	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		SetMove(float4::LEFT * GameEngineTime::GetDeltaTime() * Speed);
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		
		SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * Speed);
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		SetMove(float4::UP * GameEngineTime::GetDeltaTime() * Speed);
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * Speed);
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
		PlayerStat->Hp_ -= 10;
		
		float newSize = Hp_BarSize_.x * (PlayerStat->Hp_ / 100);
		Hp_BarPivot_ = float4{ 0 - ((Hp_BarSize_.x - newSize)/2), Hp_BarRed_->GetPivot().y };
		Hp_BarRed_->SetScale(float4{ newSize, Hp_BarSize_.y });
		Hp_BarRed_->SetPivot(Hp_BarPivot_);
	}
	// ~삭제해도 됨 삭제해도 됨 삭제해도 됨 삭제해도 됨 삭제해도 됨 삭제해도 됨
}

void Player::Render()
{

}

void Player::KillPlayer()
{
	GameEngineUpdateObject::Death();
}

