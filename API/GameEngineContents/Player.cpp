#include "Player.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineImage.h>
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
	: Hp_BarRed_(nullptr)
	, PlayerRenderer_(nullptr)
	, Gravity_(100.0f)
{

}

Player::~Player() 
{
}

void Player::Start()
{
	SetPosition({ 200, 600 });
	SetScale({ 100, 100 });

	// 플레이어 이미지 관련 설정
	PlayerInfo::GetInst()->ChangeCharacter(Character::Type::Cavallo);

	PlayerRenderer_ = CreateRenderer();
	PlayerRenderer_->CreateAnimation("Cavallo_WalkRight.bmp", "Idle_Right", 0, 0, 0.1f, false);
	PlayerRenderer_->CreateAnimation("Cavallo_WalkRight.bmp", "Walk_Right", 0, 3, 0.12f, true);
	PlayerRenderer_->CreateAnimation("Cavallo_WalkLeft.bmp", "Walk_Left", 0, 3, 0.12f, true);
	PlayerRenderer_->ChangeAnimation("Idle_Right"); 


	CreateRenderer("hpbar_back.bmp", RenderPivot::CENTER, { 0, 40 });
	Hp_BarRed_ = CreateRenderer("hpbar.bmp", RenderPivot::CENTER, { 0, 40 });
	Hp_BarSize_ = Hp_BarRed_->GetScale();


	MapColImage_ = GameEngineImageManager::GetInst()->Find("Library_Books_x2_Col.bmp");
}

void Player::Update()
{
	

	if (nullptr == MapColImage_)
	{
		MsgBoxAssert("맵 콜라이더가 로드되지 않았습니다");
	}

	PlayerStat_ = PlayerInfo::GetInst()->Character_;
	float Speed = PlayerStat_->Speed_;
	
	float4 CheckPos;
	float4 MoveDir = float4::ZERO;


	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		MoveDir = float4::LEFT;
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		MoveDir = float4::RIGHT;
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		MoveDir = float4::UP;
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		MoveDir = float4::DOWN;
	}

	if (true == GameEngineInput::GetInst()->IsDown("SpaceBar"))
	{
		Projectile* Bullet = GetLevel()->CreateActor<Projectile>();
		Bullet->SetPosition(GetPosition());
	}

	// 중력 적용
	/*AccGravity_ += GameEngineTime::GetDeltaTime() * Gravity_;
	SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * AccGravity_);*/
	
	// Pixel 충돌
	float4 NextPosTop = GetPosition() + (MoveDir * GameEngineTime::GetDeltaTime() * Speed) + float4(0, -40);
	float4 NextPosBot = GetPosition() + (MoveDir * GameEngineTime::GetDeltaTime() * Speed) + float4(0, 40);

	int NextTopColor = MapColImage_->GetImagePixel(NextPosTop);
	int NextBotColor = MapColImage_->GetImagePixel(NextPosBot);
	if (RGB(0, 0, 0) == NextTopColor || RGB(0, 0, 0) == NextBotColor)
	{
		Speed = 0;
	}

	if (MoveDir == float4::LEFT)
	{
		PlayerRenderer_->ChangeAnimation("Walk_Left");
	}
	else if (MoveDir == float4::RIGHT)
	{
		PlayerRenderer_->ChangeAnimation("Walk_Right");
	}
	else
	{
		PlayerRenderer_->ChangeAnimation("Idle_Right");
	}
	SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed);
	
	GetLevel()->SetCameraPos(GetPosition() - GameEngineWindow::GetScale().Half());
	

	// 삭제해도 됨 삭제해도 됨 삭제해도 됨 삭제해도 됨 삭제해도 됨 삭제해도 됨
	if (true == GameEngineInput::GetInst()->IsDown("KillPlayer"))
	{
		KillPlayer();
	}

	if (true == GameEngineInput::GetInst()->IsDown("PlayerDamaged"))
	{
		PlayerStat_->Hp_ -= 10;

	}
	// ~삭제해도 됨 삭제해도 됨 삭제해도 됨 삭제해도 됨 삭제해도 됨 삭제해도 됨
}

void Player::Render()
{

	// 체력 바
	float newSize = Hp_BarSize_.x * (PlayerStat_->Hp_ / 100);
	Hp_BarPivot_ = float4{ 0 - ((Hp_BarSize_.x - newSize) / 2), Hp_BarRed_->GetPivot().y };
	Hp_BarRed_->SetScale(float4{ newSize, Hp_BarSize_.y });
	Hp_BarRed_->SetPivot(Hp_BarPivot_);
}

void Player::KillPlayer()
{
	GameEngineUpdateObject::Death();
}

