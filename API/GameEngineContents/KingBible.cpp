#include "KingBible.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GameEnum.h"

KingBible::KingBible()
	: State_(STATE::NONE)
	, IsBullet_(false)
	, Alpha_(0.0f)
{
}

KingBible::~KingBible() 
{
}

void KingBible::Start()
{
	NextLevelOff();

	// 최대 5권
	Bibles_.reserve(5);

	ChangeState(STATE::SPIN);
}

void KingBible::Update()
{

	PlayerPos_ = GameInfo::GetPlayerInfo()->PlayerPos_;
	DeltaTime_ = GameEngineTime::GetDeltaTime(static_cast<int>(TIME_GROUP::WEAPON));
	SetPosition(PlayerPos_);

	// 스탯
	Level_ = GameInfo::GetPlayerInfo()->AllSkillLevel_[SkillType::KINGBIBLE];
	Bible_ = GameInfo::AllSkillStat_[SkillType::KINGBIBLE];
	SetDamage(Bible_[Level_].Damage_);

	StateUpdate();
}

void KingBible::StateUpdate()
{
	switch (State_)
	{
	case KingBible::STATE::SPIN:
		SpinUpdate();
		break;
	case KingBible::STATE::VANISH:
		VanishUpdate();
		break;
	default:
		break;
	}
}

void KingBible::ChangeState(STATE _State)
{
	if (State_ != _State)
	{
		switch (_State)
		{
		case KingBible::STATE::SPIN:
			SpinStart();
			break;
		case KingBible::STATE::VANISH:
			VanishStart();
			break;
		default:
			break;
		}
	}

	State_ = _State;
}

void KingBible::SpinStart()
{
	// 초기설정
	BookCount_ = Bible_[Level_].SkillCount_;
	Range_ = GameInfo::GetPlayerInfo()->MeleeRange_ * 80.0f;
	
	DurationCounter_.SetCount(Bible_[Level_].Duration_); // 불투명 시간
	CoolTimeCounter_.SetCount(Bible_[Level_].CoolTime_); // 투명한 시간

	Bibles_.clear();
	// 개수대로 배치
	for (int i = 0; i < BookCount_; i++)
	{
		// 렌더러, 콜리전, 각도
		GameEngineRenderer* Renderer = CreateRenderer("KingBible.bmp", static_cast<int>(RENDER_ORDER::WEAPON));
		GameEngineCollision* Collision = CreateCollision("PlayerAttack", Renderer->GetScale());
		Bibles_.push_back(Bible{ Renderer, Collision });

		// 2권 360 / 2 == 180
		float Degree = static_cast<float>(360 / BookCount_);
		float4 SetDir = float4::VectorRotationToDegreeZ(float4::RIGHT * 80.0f, i * Degree);
		Bibles_[i].SetRCPivot(SetDir);
		Bibles_[i].BookCollision_->On();
	}

}

void KingBible::SpinUpdate()
{
	// 페이드 인
	// 레벨 정보를 통해 지속시간 후 Vanish

	for (Bible Book : Bibles_)
	{
		float4 CurDir = Book.BookRenderer_->GetPivot();
		float4 RotDir = float4::VectorRotationToRadianZ(CurDir, GameEngineMath::PIE2 * DeltaTime_);
		Book.SetRCPivot(RotDir);

		AlphaDelta_ += DeltaTime_ / 2.0f;
		int Alpha = static_cast<int>(GameEngineMath::LerpLimit(0, 255, AlphaDelta_));

		Book.BookRenderer_->SetAlpha(Alpha);
	}

	if (true == DurationCounter_.Start(DeltaTime_))
	{
		AlphaDelta_ = 0;
		ChangeState(STATE::VANISH);
	}

}

void KingBible::VanishStart()
{
	// 페이드 아웃
	for (Bible Book : Bibles_)
	{
		Book.BookCollision_->Off();
	}
}

void KingBible::VanishUpdate()
{
	for (Bible Book : Bibles_)
	{
		float4 CurDir = Book.BookRenderer_->GetPivot();
		float4 RotDir = float4::VectorRotationToRadianZ(CurDir, GameEngineMath::PIE2 * DeltaTime_);
		Book.SetRCPivot(RotDir);

		AlphaDelta_ += DeltaTime_ / 2.0f;
		int Alpha = static_cast<int>(GameEngineMath::LerpLimit(255, 0, AlphaDelta_));

		Book.BookRenderer_->SetAlpha(Alpha);
	}

	// 쿨타임 능력치 확인해서 시간 지났으면 Spin
	if (true == CoolTimeCounter_.Start(DeltaTime_))
	{
		AlphaDelta_ = 0;
		ChangeState(STATE::SPIN);
	}
}

void KingBible::Bible::SetRCPivot(float4 _Pivot)
{
	BookRenderer_->SetPivot(_Pivot);
	BookCollision_->SetPivot(_Pivot);
}
