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
#include <GameEngineBase/GameEngineRandom.h>

#include "GameEnum.h"
#include "GameInfo.h"
#include "Character.h"

#include "Vector2D.h"
#include "ProjectileShooter.h"
#include "PlayLevel.h"
#include "Enemy.h"


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
	SetPosition({ 1710, 770 });
	SetScale({ 100, 100 });

	// 플레이어 이미지, 애니메이션 관련 설정
	GameInfo::SetCharacter(CharacterType::Cavallo);	// 디버그용도 : 플레이 레벨에서 시작하기 때문에 설정
	GameInfo::SetPlayerInfo();	// 선택한 캐릭터정보를 플레이어정보로 세팅
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
	CreateRenderer("hpbar_back.bmp", static_cast<int>(RENDER_ORDER::PLAYER), RenderPivot::CENTER, {0, 35});
	Hp_BarRed_ = CreateRenderer("hpbar.bmp", static_cast<int>(RENDER_ORDER::PLAYER), RenderPivot::CENTER, { 0, 35 });
	Hp_BarSize_ = Hp_BarRed_->GetScale();


	// 충돌
	MapColImage_ = PlayLevel::MapColImage_;

	PlayerCol_ = CreateCollision("Player", { 40, 40 });
	PlayerShootRange_ = CreateCollision("PlayerShootRange", { 600, 600 });
	PlayerShootRange_->Off();

	// 슈팅
	MagicShooter_ = GetLevel()->CreateActor<ProjectileShooter>(static_cast<int>(RENDER_ORDER::PLAYER), "Shooter");
	MagicShooter_->SetShooter(SkillType::MAGICWAND , BulletType::FLAME_BLUE, 2, 0.08f, 2.0f, 1.0f);

	KnifeShooter_ = GetLevel()->CreateActor<ProjectileShooter>(static_cast<int>(RENDER_ORDER::PLAYER), "Shooter");
	KnifeShooter_->SetShooter(SkillType::KNIFE, BulletType::KNIFE, 2, 0.1f, 2.0f, 1.0f);

	FireShooter_ = GetLevel()->CreateActor<ProjectileShooter>(static_cast<int>(RENDER_ORDER::PLAYER), "Shooter");
	FireShooter_->SetShooter(SkillType::FIREWAND, BulletType::FLAME_RED, 1, 0.0f, 4.0f, 1.0f);
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

	float Speed = MapColCheck(Speed_);
	SetMove(MoveDir_ * GameEngineTime::GetDeltaTime(static_cast<int>(TIME_GROUP::PLAYER)) * Speed);

	// 중력 적용
	/*AccGravity_ += GameEngineTime::GetDeltaTime() * Gravity_;
	SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * AccGravity_);*/

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
	EnemyAttackCheck();


}

float Player::MapColCheck(float _PlayerSpeed)
{
	// InfiniteMap에 의해 맵 렌더러는 움직이지만
	// MapColImage는 움직이지 않는다

	// 움직임이 없으면 체크할 필요 없음
	if (MoveDir_.x == 0.0f && MoveDir_.y == 0.0f)
	{
		return _PlayerSpeed;
	}

	int PlayerPosX = GetPosition().ix() % MapColImage_->GetScale().ix();
	if (PlayerPosX < 0)
	{
		PlayerPosX = PlayerPosX + MapColImage_->GetScale().ix();
	}

	float4 PlayerColPos = { static_cast<float>(PlayerPosX), GetPosition().y };
	
	int ColorTop = MapColImage_->GetImagePixel(PlayerColPos + float4{ 0, -20});
	int ColorBot = MapColImage_->GetImagePixel(PlayerColPos + float4{ 0, 20});
	int ColorLeft = MapColImage_->GetImagePixel(PlayerColPos + float4{ -20, 0});
	int ColorRight = MapColImage_->GetImagePixel(PlayerColPos + float4{ 20, 0});

	if (RGB(0, 0, 0) == ColorTop && MoveDir_.y < 0.0f)
	{
		return 0.0f;
	}

	if (RGB(0, 0, 0) == ColorBot && MoveDir_.y > 0.0f)
	{
		return 0.0f;
	}

	if (RGB(0, 0, 0) == ColorLeft && MoveDir_.x < 0.0f)
	{
		return 0.0f;
	}

	if (RGB(0, 0, 0) == ColorRight && MoveDir_.x > 0.0f)
	{
		return 0.0f;
	}

	return _PlayerSpeed;
}

void Player::EnemyAttackCheck()
{
	EnemyBump_ = false;
	if (nullptr != PlayerCol_)
	{
		EnemyBump_ = PlayerCol_->CollisionResult("Enemy", BumpEnemy_,CollisionType::Rect, CollisionType::Rect);
	}

	if (true == EnemyBump_ )
	{
		Enemy* Ptr = dynamic_cast<Enemy*>(BumpEnemy_[0]->GetActor());
		BumpEnemy_.clear();
		if (false == Ptr->IsDead())
		{
			Attacked(10);
		}
	}

	if (false == Hitable_)
	{
		InvincibleTime_ -= GameEngineTime::GetDeltaTime();
	}

	if (0 >= InvincibleTime_)
	{
		Hitable_ = true;
		InvincibleTime_ = HitTime_;
	}
}



float4 Player::ShootableEnemeyCheck()
{
	GameEngineRandom Random;

	if (true == PlayerShootRange_->CollisionResult("Enemy", ShootableEnemy_, CollisionType::Rect, CollisionType::Rect))
	{
		int Index = Random.RandomInt(0, static_cast<int>(ShootableEnemy_.size()) - 1);
		float4 MonsterPos = ShootableEnemy_[Index]->GetCollisionPos();
		ShootableEnemy_.clear();

		return MonsterPos;
	}

	// 몬스터가 없다면 랜덤 방향
	float4 RandomDir = float4{ Random.RandomFloat(-1, 1), Random.RandomFloat(-1, 1) };

	return GetPosition() + RandomDir;
}

void Player::Shooting()
{
	float4 MonsterPos = ShootableEnemeyCheck();

	int* SkillLevelInfo = GameInfo::GetPlayerInfo()->SkillLevelInfo_;

	if (0 < SkillLevelInfo[static_cast<int>(SkillType::KNIFE)])
	{
		KnifeShooter_->Shooting(GameEngineTime::GetDeltaTime(static_cast<int>(TIME_GROUP::WEAPON)), PlayerPos_, MonsterPos, MoveDir_);
	}

	if (0 < SkillLevelInfo[static_cast<int>(SkillType::MAGICWAND)])
	{
		MagicShooter_->Shooting(GameEngineTime::GetDeltaTime(static_cast<int>(TIME_GROUP::WEAPON)), PlayerPos_, MonsterPos);
	}

	if (0 < SkillLevelInfo[static_cast<int>(SkillType::FIREWAND)])
	{
		FireShooter_->Shooting(GameEngineTime::GetDeltaTime(static_cast<int>(TIME_GROUP::WEAPON)), PlayerPos_, MonsterPos);
	}
}


