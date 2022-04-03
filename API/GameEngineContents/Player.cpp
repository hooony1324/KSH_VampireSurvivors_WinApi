#include "Player.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

// 총알
#include <GameEngine/GameEngineLevel.h>
#include "Projectile.h"

#include "Character.h"
#include "PlayerInfo.h"

#include <GameEngine/GameEngineRenderer.h>
#include <cmath>

Player::Player() 
	: Hp_BarRed_(nullptr)
	, PlayerRenderer_(nullptr)
	, Gravity_(100.0f)
	, MoveDir_(float4::ZERO)
	, HeadDir_(float4::RIGHT)
	, Hitable_(true)
	, HitTime_(1.0f)
{
	InvincibleTime_ = HitTime_;
}

Player::~Player() 
{
}

void Player::Start()
{
	SetPosition({ 800, 800 });
	SetScale({ 100, 100 });

	// 플레이어 이미지, 애니메이션 관련 설정
	PlayerInfo::GetInst()->ChangeCharacter(Character::Type::Cavallo);
	PlayerStat_ = PlayerInfo::GetInst()->GetCharacter();

	PlayerRenderer_ = CreateRenderer();
	PlayerRenderer_->CreateAnimation(PlayerStat_->WalkRightAnim_, "Idle_Right", 0, 0, 0.1f, false);
	PlayerRenderer_->CreateAnimation(PlayerStat_->WalkRightAnim_, "Walk_Right", 0, 3, 0.12f, true);
	PlayerRenderer_->CreateAnimation(PlayerStat_->WalkLeftAnim_, "Idle_Left", 0, 0, 0.1f, false);
	PlayerRenderer_->CreateAnimation(PlayerStat_->WalkLeftAnim_, "Walk_Left", 0, 3, 0.12f, true);
	PlayerRenderer_->ChangeAnimation("Idle_Right"); 

	// -체력바
	CreateRenderer("hpbar_back.bmp", RenderPivot::CENTER, { 0, 40 });
	Hp_BarRed_ = CreateRenderer("hpbar.bmp", RenderPivot::CENTER, { 0, 40 });
	Hp_BarSize_ = Hp_BarRed_->GetScale();

	MapColImage_ = GameEngineImageManager::GetInst()->Find("Library_Books_x2_Col.bmp");

	if (nullptr == MapColImage_)
	{
		MsgBoxAssert("맵 콜라이더가 로드되지 않았습니다");
	}

	// 충돌 테스트
	PlayerCol_ = CreateCollision("Player", { 35, 45 });

	// 몬스터가 충돌하면 리스폰
	EnemyCollectorL_ = CreateCollision("EnemyCollector", { 30, 700 }, { -400, 0 });
	EnemyCollectorR_ = CreateCollision("EnemyCollector", { 30, 700 }, { 400, 0 });
}

void Player::Update()
{
	PlayerStat_ = PlayerInfo::GetInst()->GetCharacter();
	PlayerPos_ = GetPosition();
	PlayerInfo::GetInst()->GetCharacter()->SetPos(PlayerPos_);

	PlayerMove();


	if (true == GameEngineInput::GetInst()->IsDown("SpaceBar"))
	{
		float4 cPos = GetCameraEffectPosition();
		Shoot(float4::RIGHT);
	}

	GetLevel()->SetCameraPos(PlayerPos_ - GameEngineWindow::GetScale().Half());


	// 충돌 테스트
	bool BumpMonster = false;
	if (nullptr != PlayerCol_)
	{
		BumpMonster = PlayerCol_->CollisionCheck("Monster", CollisionType::Rect, CollisionType::Rect);
	}
	if (true == BumpMonster)
	{
		Attacked(90);
	}
	{
		if (false == Hitable_)
		InvincibleTime_ -= GameEngineTime::GetDeltaTime();
		if (0 >= InvincibleTime_)
		{
			Hitable_ = true;
			InvincibleTime_ = HitTime_;
		}
	}

}

void Player::Render()
{
	HpBarRender();

}

void Player::PlayerMove()
{
	float Speed = PlayerStat_->Speed_;
	MoveDir_ = float4::ZERO;

	bool MoveLeft = GameEngineInput::GetInst()->IsPress("MoveLeft");
	bool MoveRight = GameEngineInput::GetInst()->IsPress("MoveRight");
	bool MoveUp = GameEngineInput::GetInst()->IsPress("MoveUp");
	bool MoveDown = GameEngineInput::GetInst()->IsPress("MoveDown");

	bool StopLeft = GameEngineInput::GetInst()->IsUp("MoveLeft");
	bool StopRight = GameEngineInput::GetInst()->IsUp("MoveRight");
	bool StopUp = GameEngineInput::GetInst()->IsUp("MoveUp");
	bool StopDown = GameEngineInput::GetInst()->IsUp("MoveDown");

	if (MoveLeft)
	{
		MoveDir_ = float4::LEFT;
		HeadDir_ = float4::LEFT;
	}

	if (MoveRight)
	{
		MoveDir_ = float4::RIGHT;
		HeadDir_ = float4::RIGHT;
	}

	if (MoveUp)
	{
		MoveDir_ = float4::UP;
	}

	if (MoveDown)
	{
		MoveDir_ = float4::DOWN;
	}

	if (MoveLeft && MoveUp)
	{
		MoveDir_ = (float4::LEFT + float4::UP) * (float)(1 / sqrt(2));
	}

	if (MoveUp && MoveRight)
	{
		MoveDir_ = (float4::UP + float4::RIGHT) * (float)(1 / sqrt(2));
	}

	if (MoveRight && MoveDown)
	{
		MoveDir_ = (float4::RIGHT + float4::DOWN) * (float)(1 / sqrt(2));
	}

	if (MoveDown && MoveLeft)
	{
		MoveDir_ = (float4::DOWN + float4::LEFT) * (float)(1 / sqrt(2));
	}



	// 중력 적용
	/*AccGravity_ += GameEngineTime::GetDeltaTime() * Gravity_;
	SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * AccGravity_);*/

	// Pixel 충돌
	float4 NextPosTop = PlayerPos_ + (MoveDir_ * GameEngineTime::GetDeltaTime() * Speed) + float4(0, -40);
	float4 NextPosBot = PlayerPos_ + (MoveDir_ * GameEngineTime::GetDeltaTime() * Speed) + float4(0, 40);

	int NextTopColor = MapColImage_->GetImagePixel(NextPosTop);
	int NextBotColor = MapColImage_->GetImagePixel(NextPosBot);
	if (RGB(0, 0, 0) == NextTopColor || RGB(0, 0, 0) == NextBotColor)
	{
		Speed = 0;
	}

	if (HeadDir_ == float4::LEFT && MoveDir_ != float4::ZERO)
	{
		PlayerRenderer_->ChangeAnimation("Walk_Left");
	}
	else if (MoveDir_ != float4::ZERO)
	{
		PlayerRenderer_->ChangeAnimation("Walk_Right");
	}

	SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * Speed);

	if (StopLeft || StopRight || StopUp || StopDown)
	{
		if (HeadDir_ == float4::RIGHT)
		{
			PlayerRenderer_->ChangeAnimation("Idle_Right");
		}
		else
		{
			PlayerRenderer_->ChangeAnimation("Idle_Left");
		}
	}
}

void Player::KillPlayer()
{
	EnemyCollectorL_->Death();
	EnemyCollectorR_->Death();
	PlayerCol_->Death();
	GameEngineUpdateObject::Death();
}

void Player::Attacked(int _Damage)
{
	if (false == Hitable_ || true == IsDeath())
	{
		return;
	}

	PlayerStat_->Hp_ -= _Damage;
	Hitable_ = false;

	if (PlayerStat_->Hp_ <= 0)
	{
		// 예시
		// PlayerRenderer_->ChangeAnimation("CavalloDead");
		GameEngine::GetInst().ChangeLevel("Result");
	}
}

void Player::HpBarRender()
{
	// 체력 바
	float newSize = Hp_BarSize_.x * (PlayerStat_->Hp_ / 100);
	Hp_BarPivot_ = float4{ 0 - ((Hp_BarSize_.x - newSize) / 2), Hp_BarRed_->GetPivot().y };
	Hp_BarRed_->SetScale(float4{ newSize, Hp_BarSize_.y });
	Hp_BarRed_->SetPivot(Hp_BarPivot_);
}

void Player::Shoot(float4 _ShootDir)
{
	Projectile* Bullet = GetLevel()->CreateActor<Projectile>();
	Bullet->Death(5);
	Bullet->SetPosition(PlayerPos_);
}


