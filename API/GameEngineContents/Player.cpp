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

#include "ObjectOrder.h"
#include "Character.h"

#include "GameInfo.h"

#include "Vector2D.h"
#include "Projectile.h"
#include "ExpGem.h"



Player::Player() 
	: Hp_BarRed_(nullptr)
	, PlayerRenderer_(nullptr)
	, MoveDir_(float4::ZERO)
	, HeadDir_(-1)
	, Hitable_(true)
	, HitTime_(1.0f)
{
	// ���� ������ �����ð����� ����
	InvincibleTime_ = HitTime_;
}

Player::~Player() 
{
}

void Player::Start()
{
	SetPosition({ 1000, 700 });
	SetScale({ 100, 100 });

	// �÷��̾� �̹���, �ִϸ��̼� ���� ����
	GameInfo::SetCharacter(CharacterType::Cavallo);	// ����׿뵵 : �÷��� �������� �����ϱ� ������ ����
	GameInfo::SetPlayerInfo();
	CharacterStat_ = GameInfo::GetCharacter();

	PlayerRenderer_ = CreateRenderer();
	PlayerRenderer_->CreateAnimation(CharacterStat_->WalkRightAnim_, "Idle_Right", 0, 0, 0.1f, false);
	PlayerRenderer_->CreateAnimation(CharacterStat_->WalkRightAnim_, "Walk_Right", 0, 3, 0.12f, true);
	PlayerRenderer_->CreateAnimation(CharacterStat_->WalkLeftAnim_, "Idle_Left", 0, 0, 0.1f, false);
	PlayerRenderer_->CreateAnimation(CharacterStat_->WalkLeftAnim_, "Walk_Left", 0, 3, 0.12f, true);
	PlayerRenderer_->ChangeAnimation("Idle_Right"); 

	// ó������ Character�� ������ ����
	// �̵��ӵ�, ü��
	Speed_ = CharacterStat_->Speed_;

	// ü�¹�
	CreateRenderer("hpbar_back.bmp", static_cast<int>(RENDER_ORDER::PLAYER), RenderPivot::CENTER, {0, 40});
	Hp_BarRed_ = CreateRenderer("hpbar.bmp", static_cast<int>(RENDER_ORDER::PLAYER), RenderPivot::CENTER, { 0, 40 });
	Hp_BarSize_ = Hp_BarRed_->GetScale();


	// �浹
	PlayerCol_ = CreateCollision("Player", { 40, 40 });
}

void Player::Update()
{
	SetGameInfo();
	

	MonsterAttPlayer();
	AllCollisionCheck();

	PlayerMove();

	GetLevel()->SetCameraPos(PlayerPos_ - GameEngineWindow::GetScale().Half());
}

void Player::Render()
{
	HpBarRender();

	Vector2D::DebugVectorRender(this);
}

void Player::SetGameInfo()
{
	GameInfo::GetPlayerInfo()->PlayerPos_ = GetPosition();
}

void Player::PlayerMove()
{
	PlayerPos_ = GetPosition();

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
		MoveDir_ += float4::LEFT;
		HeadDir_ = -1;
	}

	if (MoveRight)
	{
		MoveDir_ += float4::RIGHT;
		HeadDir_ = 1;
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

	// �Ӹ� ���⿡ ���� Idle�ִϸ��̼�
	if (HeadDir_ == -1 && ( MoveDir_.x != 0 || MoveDir_.y != 0))
	{
		PlayerRenderer_->ChangeAnimation("Walk_Left");
	}
	else if (HeadDir_ == 1 && ( MoveDir_.x != 0 || MoveDir_.y != 0 ))
	{
		PlayerRenderer_->ChangeAnimation("Walk_Right");
	}

	SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);

	// �����̰� �� �Ŀ� Idle�ִϸ��̼�
	if (StopLeft || StopRight || StopUp || StopDown)
	{
		if (HeadDir_ == 1)
		{
			PlayerRenderer_->ChangeAnimation("Idle_Right");
		}
		else if (HeadDir_ == -1)
		{
			PlayerRenderer_->ChangeAnimation("Idle_Left");
		}
	}

	// �߷� ����
	/*AccGravity_ += GameEngineTime::GetDeltaTime() * Gravity_;
	SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * AccGravity_);*/

	// Pixel �浹
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
	// ü�� ��
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

	float CurrentHp = GameInfo::GetPlayerInfo()->CurrentHp_ -= _Damage;
	Hitable_ = false;

	if (CurrentHp <= 0)
	{
		// ����
		// PlayerRenderer_->ChangeAnimation("CavalloDead");
		GameEngine::GetInst().ChangeLevel("Result");
	}
}

void Player::MonsterAttPlayer()
{
	bool BumpMonster = false;
	if (nullptr != PlayerCol_)
	{
		BumpMonster = PlayerCol_->CollisionCheck("Monster", CollisionType::Rect, CollisionType::Rect);
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

void Player::AllCollisionCheck()
{
	// exp ����
	std::vector<GameEngineCollision*> Result;
	if (true == PlayerCol_->CollisionResult("ExpGem", Result, CollisionType::Rect, CollisionType::Rect))
	{
		ExpGem* GemPtr = dynamic_cast<ExpGem*>(Result[0]->GetActor());
		float Exp = GemPtr->GetExp();

		GameInfo::GetPlayerInfo()->CurrentExp_ += Exp; // �÷��̾� ���� �������� ȹ��� ����������

		GemPtr->Death();
	}

}

