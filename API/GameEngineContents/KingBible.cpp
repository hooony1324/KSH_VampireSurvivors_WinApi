#include "KingBible.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GameEnum.h"

KingBible::KingBible() 
{
}

KingBible::~KingBible() 
{
}

void KingBible::Start()
{
	NextLevelOff();

	BookRenderer_ = CreateRenderer("KingBible.bmp", static_cast<int>(RENDER_ORDER::WEAPON));

}

void KingBible::Update()
{
	SetPosition(GameInfo::GetPlayerInfo()->PlayerPos_);
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
	// 레벨 정보를 통해 책이 몇 권 인지를 갱신
	Level_ = GameInfo::GetPlayerInfo()->AllSkillLevel_[SkillType::KINGBIBLE];
	Bible_ = GameInfo::AllSkillStat_[SkillType::KINGBIBLE];
	
	BookCount_ = Bible_[Level_].SkillCount_;

	// 테스토
	BookCount_ = 1;

	Range_ = GameInfo::GetPlayerInfo()->MeleeRange_ * 80.0f;
}

void KingBible::SpinUpdate()
{
	// 페이드 인
	// 레벨 정보를 통해 지속시간 후 Vanish

	// 일단 한권 돌려보자

	
}

void KingBible::VanishStart()
{
	// 페이드 아웃
}

void KingBible::VanishUpdate()
{
	// 쿨타임 능력치 확인해서 시간 지났으면 Spin
}
