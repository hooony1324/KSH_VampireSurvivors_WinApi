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
#include <GameEngine/GameEngineLevel.h>

#include "ObjectEnum.h"
#include "Character.h"

#include "GameInfo.h"

#include "Vector2D.h"
#include "ProjectileShooter.h"
#include "ExpGem.h"



Player::Player() 
	: Hp_BarRed_(nullptr)
	, PlayerRenderer_(nullptr)
	, MoveDir_(float4::ZERO)
	, HeadDir_(HeadDir::LEFT)
	, Hitable_(true)
	, HitTime_(1.0f)
	, CharacterStat_(nullptr)
	, PlayerCol_(nullptr)
	, Speed_(0)
	, PlayerShootRange_(nullptr)
{
	// 공격 맞으면 일정시간동안 무적
	InvincibleTime_ = HitTime_;
}

Player::~Player() 
{
}


void Player::Start()
{
	SetPosition({ 1000, 700 });
	SetScale({ 100, 100 });

	// 플레이어 이미지, 애니메이션 관련 설정
	GameInfo::SetCharacter(CharacterType::Cavallo);	// 디버그용도 : 플레이 레벨에서 시작하기 때문에 설정
	GameInfo::SetPlayerInfo();
	CharacterStat_ = GameInfo::GetCharacter();

	PlayerRenderer_ = CreateRenderer();
	PlayerRenderer_->CreateAnimation(CharacterStat_->WalkRightAnim_, "Idle_Right", 0, 0, 0.1f, false);
	PlayerRenderer_->CreateAnimation(CharacterStat_->WalkRightAnim_, "Walk_Right", 0, 3, 0.12f, true);
	PlayerRenderer_->CreateAnimation(CharacterStat_->WalkLeftAnim_, "Idle_Left", 0, 0, 0.1f, false);
	PlayerRenderer_->CreateAnimation(CharacterStat_->WalkLeftAnim_, "Walk_Left", 0, 3, 0.12f, true);
	PlayerRenderer_->ChangeAnimation("Idle_Right"); 

	// 처음에는 선택된 Character의 스탯을 따름
	// 이동속도, 체력
	Speed_ = CharacterStat_->Speed_;

	// 체력바
	CreateRenderer("hpbar_back.bmp", static_cast<int>(RENDER_ORDER::PLAYER), RenderPivot::CENTER, {0, 40});
	Hp_BarRed_ = CreateRenderer("hpbar.bmp", static_cast<int>(RENDER_ORDER::PLAYER), RenderPivot::CENTER, { 0, 40 });
	Hp_BarSize_ = Hp_BarRed_->GetScale();


	// 충돌
	PlayerCol_ = CreateCollision("Player", { 40, 40 });
	PlayerShootRange_ = CreateCollision("PlayerShootRange", { 600, 600 });
	PlayerShootRange_->Off(); // 디버그시 안보이게

	// 슈팅
	Shooter1_ = GetLevel()->CreateActor<ProjectileShooter>(static_cast<int>(RENDER_ORDER::PLAYER), "Shooter");
	Shooter1_->InitShooter(BulletType::FLAME_BLUE, 2, 0.12f, 2.0f, 1.0f);
}

void Player::Update()
{
	// 일시정지
	if (0.5f > GameEngineTime::GetInst()->GetTimeScale(static_cast<int>(TIME_GROUP::PLAYER)))
	{
		return;
	}

	// 게임정보 업데이트
	SetGameInfo();

	// 충돌체크
	AllCollisionCheck();

	// 플레이어
	PlayerMove();
	Shooting();

	// 카메라
	GetLevel()->SetCameraPos(PlayerPos_ - GameEngineWindow::GetScale().Half());
}

void Player::Render()
{
	HpBarRender();

	//Vector2D::DebugVectorRender(this);
}

void Player::SetGameInfo()
{
	PlayerPos_ = GetPosition();
	GameInfo::GetPlayerInfo()->PlayerPos_ = PlayerPos_;

}

void Player::PlayerMove()
{
	bool StopLeft = GameEngineInput::GetInst()->IsFree("MoveLeft");
	bool StopRight = GameEngineInput::GetInst()->IsFree("MoveRight");
	bool StopUp = GameEngineInput::GetInst()->IsFree("MoveUp");
	bool StopDown = GameEngineInput::GetInst()->IsFree("MoveDown");

	// 움직이고 난 후에 Idle애니메이션
	if (StopLeft && StopRight && StopUp && StopDown)
	{
		if (HeadDir_ == HeadDir::RIGHT)
		{
			PlayerRenderer_->ChangeAnimation("Idle_Right");
		}
		else if (HeadDir_ == HeadDir::LEFT)
		{
			PlayerRenderer_->ChangeAnimation("Idle_Left");
		}

		return;
	}

	MoveDir_ = float4::ZERO;
	bool MoveLeft = GameEngineInput::GetInst()->IsPress("MoveLeft");
	bool MoveRight = GameEngineInput::GetInst()->IsPress("MoveRight");
	bool MoveUp = GameEngineInput::GetInst()->IsPress("MoveUp");
	bool MoveDown = GameEngineInput::GetInst()->IsPress("MoveDown");

	if (MoveLeft)
	{
		MoveDir_ += float4::LEFT;
		HeadDir_ = HeadDir::LEFT;
	}

	if (MoveRight)
	{
		MoveDir_ += float4::RIGHT;
		HeadDir_ = HeadDir::RIGHT;
	}

	if (MoveUp)
	{
		MoveDir_ += float4::UP;
	}

	if (MoveDown)
	{
		MoveDir_ += float4::DOWN;
	}

	MoveDir_.Normal2D();

	// 머리 방향에 따른 Idle애니메이션
	if (HeadDir::LEFT == HeadDir_)
	{
		PlayerRenderer_->ChangeAnimation("Walk_Left");
	}
	else
	{
		PlayerRenderer_->ChangeAnimation("Walk_Right");
	}

	SetMove(MoveDir_ * GameEngineTime::GetDeltaTime(static_cast<int>(TIME_GROUP::PLAYER)) * Speed_);

	// 중력 적용
	/*AccGravity_ += GameEngineTime::GetDeltaTime() * Gravity_;
	SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * AccGravity_);*/

	// Pixel 충돌
	//float4 NextPosTop = PlayerPos_ + (MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_) + float4(0, -40);
	//float4 NextPosBot = PlayerPos_ + (MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_) + float4(0, 40);
	//int NextTopColor = MapColImage_->GetImagePixel(NextPosTop);
	//int NextBotColor = MapColImage_->GetImagePixel(NextPosBot);
	//if (RGB(0, 0, 0) == NextTopColor || RGB(0, 0, 0) == NextBotColor)
	//{
	//	Speed = 0;
	//}
}

void Player::HpBarRender()
{
	// 체력 바
	float CurrentHp = GameInfo::GetPlayerInfo()->CurrentHp_;
	float MaxHp = GameInfo::GetPlayerInfo()->MaxHp_;
	float Ratio = CurrentHp / MaxHp;
	float NewSizeX = Hp_BarSize_.x * Ratio;
	float4 Hp_BarPivot = float4{ 0 - ((Hp_BarSize_.x - NewSizeX) / 2), Hp_BarRed_->GetPivot().y };
	Hp_BarRed_->SetScale(float4{ NewSizeX, Hp_BarSize_.y });
	Hp_BarRed_->SetPivot(Hp_BarPivot);
	
}

void Player::Attacked(int _Damage)
{
	if (false == Hitable_ || true == IsDeath())
	{
		return;
	}

	GameEngineSound::SoundPlayOneShot("PlayerAttacked.MP3", 0);
	float CurrentHp = GameInfo::GetPlayerInfo()->CurrentHp_ -= _Damage;
	Hitable_ = false;

	if (CurrentHp <= 0)
	{
		// 예시
		//PlayerRenderer_->ChangeAnimation("CavalloDead");
		GameEngine::GetInst().ChangeLevel("Result");
	}
}


void Player::AllCollisionCheck()
{
	MonsterAttackCheck();


}

void Player::MonsterAttackCheck()
{
	bool BumpMonster = false;
	if (nullptr != PlayerCol_)
	{
		BumpMonster = PlayerCol_->CollisionCheck("Enemy", CollisionType::Rect, CollisionType::Rect);
	}

	if (true == BumpMonster)
	{
		Attacked(10);
	}

	if (false == Hitable_)
		InvincibleTime_ -= GameEngineTime::GetDeltaTime();

	if (0 >= InvincibleTime_)
	{
		Hitable_ = true;
		InvincibleTime_ = HitTime_;
	}
}


void Player::ClearBullets()
{
}

float4 Player::ShootableEnemeyCheck()
{
	if (true == PlayerShootRange_->CollisionResult("Enemy", ShootableEnemy_, CollisionType::Rect, CollisionType::Rect))
	{
		float4 MonsterPos = ShootableEnemy_[0]->GetCollisionPos();
		ShootableEnemy_.clear();

		return MonsterPos;
	}

	// 몬스터가 없다면 랜덤 방향
	return GetPosition() + float4::RIGHT;
}

void Player::Shooting()
{
	float4 MonsterPos = ShootableEnemeyCheck();
	Shooter1_->Shooting(GameEngineTime::GetDeltaTime(static_cast<int>(TIME_GROUP::WEAPON)), PlayerPos_, MonsterPos);

}


