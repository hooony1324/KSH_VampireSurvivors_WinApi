#include "GameInfo.h"
#include <GameEngineBase/GameEngineDebug.h>

Character* GameInfo::Character_ = nullptr;
GameInfo::PlayerInfo* GameInfo::PlayerInfo_ = new PlayerInfo();
bool GameInfo::Pause_ = false;

std::map<SkillType, std::map<int, SkillStat>> GameInfo::AllSkillStat_ = SetAllSkillStat();

GameInfo::GameInfo()
{
	
}

GameInfo::~GameInfo() 
{

}

void GameInfo::SetPlayerInfo()
{
	if (nullptr == Character_)
	{
		MsgBoxAssert("캐릭터가 선택되지 않은채로 게임이 시작되었습니다");
	}

	// 경험치
	PlayerInfo_->MaxExp_ = 100;
	PlayerInfo_->CurrentExp_ = 0;
	PlayerInfo_->MaxLevel_ = 200;
	PlayerInfo_->Level_ = 1;

	// 생존시간
	PlayerInfo_->SurvivalTime_ = 0;

	// 획득 골드
	PlayerInfo_->EearnedCoin_ = 0;

	// 적 처리 수
	PlayerInfo_->KillCount_ = 0;

	// PlayerInfo <- CharacterInfo 받아오기
	PlayerInfo_->Speed_				= Character_->Speed_;
	PlayerInfo_->MaxHp_				= Character_->MaxHp_;
	PlayerInfo_->CurrentHp_			= Character_->CurrentHp_;
	PlayerInfo_->Recovery_			= Character_->Recovery_;
	PlayerInfo_->Guard_				= Character_->Guard_;
	PlayerInfo_->Power_				= Character_->Power_;
	PlayerInfo_->MeleeRange_		= Character_->MeleeRange_;
	PlayerInfo_->ShootSpeedRatio_ = Character_->ShootSpeedRatio_;
	PlayerInfo_->AddShootNum_ = Character_->AddShootNum_;
	PlayerInfo_->Duration_ = Character_->Duration_;
	PlayerInfo_->CoolTime_ = Character_->CoolTime_;

	PlayerInfo_->Luck_ = Character_->Luck_;
	PlayerInfo_->Growth_ = Character_->Growth_;
	PlayerInfo_->Greed_ = Character_->Greed_;
	PlayerInfo_->Magnet_ = Character_->Magnet_;
	PlayerInfo_->Revival_ = Character_->Revival_;

	// 초기화
	PlayerInfo_->ActiveSkillSlot_.clear();
	PlayerInfo_->PassiveSkillSlot_.clear();

	// 모든 스킬 레벨 정보 초기화
	for (int i = 0; i < EVOLVE_MAX; i++)
	{
		SkillType Type = static_cast<SkillType>(i);
		PlayerInfo_->AllSkillLevel_[Type] = 0;
	}

	// 기본 스킬 입력
	PlayerInfo_->ActiveSkillSlot_.push_back(Character_->BaseSkill_);

	// 기본스킬 레벨 입력
	PlayerInfo_->AllSkillLevel_[Character_->BaseSkill_] = 1;

}

bool GameInfo::SkillLevelFull()
{

	std::map<SkillType, int> AllSkillLevel = PlayerInfo_->AllSkillLevel_;

	for (int i = 0; i < static_cast<int>(PlayerInfo_->ActiveSkillSlot_.size()); i++)
	{
		if (SKILL_LEVELMAX > AllSkillLevel[PlayerInfo_->ActiveSkillSlot_[i]])
		{
			// 각성 타입은 스킵
			if (PlayerInfo_->ActiveSkillSlot_[i] > SkillType::MAX)
			{
				continue;
			}

			return false;
		}
	}

	for (int i = 0; i < static_cast<int>(PlayerInfo_->PassiveSkillSlot_.size()); i++)
	{
		if (SKILL_LEVELMAX > AllSkillLevel[PlayerInfo_->PassiveSkillSlot_[i]])
		{
			return false;
		}
	}

	if (PlayerInfo_->ActiveSkillSlot_.size() == ACTIVE_MAX && PlayerInfo_->PassiveSkillSlot_.size() == (int)SkillType::MAX - ACTIVE_MAX)
	{
		return true;
	}

	return false;
}

bool GameInfo::EvolveSkillLevelFull()
{
	std::map<SkillType, int> AllSkillLevel = PlayerInfo_->AllSkillLevel_;

	for (int i = 0; i < static_cast<int>(PlayerInfo_->ActiveSkillSlot_.size()); i++)
	{
		if (SKILL_LEVELMAX > AllSkillLevel[PlayerInfo_->ActiveSkillSlot_[i]])
		{
			return false;
		}
	}

	for (int i = 0; i < static_cast<int>(PlayerInfo_->PassiveSkillSlot_.size()); i++)
	{
		if (SKILL_LEVELMAX > AllSkillLevel[PlayerInfo_->PassiveSkillSlot_[i]])
		{
			return false;
		}
	}

	if (PlayerInfo_->ActiveSkillSlot_.size() == ACTIVE_MAX && PlayerInfo_->PassiveSkillSlot_.size() == (int)SkillType::MAX - ACTIVE_MAX)
	{
		return true;
	}

	return false;
}

SkillType GameInfo::SkillEvolveCheck()
{
	// 액티브 슬롯에서 8레벨 엑티브스킬 전부 확인
	SkillType MaxLevelActiveSkill = SkillType::NONE;
	for (int i = 0; i < static_cast<int>(PlayerInfo_->ActiveSkillSlot_.size()); i++)
	{
		if (8 <= PlayerInfo_->AllSkillLevel_[PlayerInfo_->ActiveSkillSlot_[i]])
		{
			MaxLevelActiveSkill = PlayerInfo_->ActiveSkillSlot_[i];

			// 그 스킬의 담당 패시브 8레벨 확인
			SkillType Combination = CombinationSkill(MaxLevelActiveSkill);
			if (8 == PlayerInfo_->AllSkillLevel_[Combination])
			{
				// 먼저 확인된 각성 스킬 리턴
				return ChangeSkill(MaxLevelActiveSkill);
			}
		}
	}

	return SkillType::NONE;
}

// 액티브의 조합용 패시브 스킬 반환
SkillType GameInfo::CombinationSkill(SkillType _Type)
{
	switch (_Type)
	{
	case SkillType::KNIFE:
		return SkillType::BRACER;
		break;
	default:
		break;
	}

	return SkillType::NONE;
}

// 액티브 스킬 -> 각성스킬  | 각성스킬 -> 액티브스킬
SkillType GameInfo::ChangeSkill(SkillType _Type)
{
	switch (_Type)
	{
	// 액티브
	case SkillType::KNIFE:
		return SkillType::THOUSANDEDGE;
		break;

	// 각성
	case SkillType::THOUSANDEDGE:
		return SkillType::KNIFE;
		break;
	}

	return SkillType::NONE;
}


void GameInfo::PushEvolvedSkill(SkillType _EvolvedType)
{
	if (_EvolvedType <= SkillType::MAX)
	{
		return;
	}

	SkillType ActiveSkill = ChangeSkill(_EvolvedType);

	// ActiveSlot의 인덱스 찾아내기
	for (int i = 0; i < static_cast<int>(PlayerInfo_->ActiveSkillSlot_.size()); i++)
	{
		if (ActiveSkill == PlayerInfo_->ActiveSkillSlot_[i])
		{
			// 기존 스킬 없앰
			PlayerInfo_->AllSkillLevel_[ActiveSkill] = -1;

			// 각성 스킬
			PlayerInfo_->ActiveSkillSlot_[i] = _EvolvedType;
			PlayerInfo_->AllSkillLevel_[_EvolvedType] = 1;
		}
	}

}


// 	std::map<SkillType, std::map<int, SkillStat>> AllSkillStat_;
std::map<SkillType, std::map<int, SkillStat>> GameInfo::SetAllSkillStat()
{
	std::map<SkillType, std::map<int, SkillStat>> AllSkillStat;

	// 탄수		인터벌		쿨타임		데미지		속도			지속시간 
	// KNIFE
	{
		std::map<int, SkillStat> Level;
		Level[1] = SkillStat{ 2, 0.1f, 2.0f, 6.5f, 550.0f, 4.0f };
		Level[2] = SkillStat{ 3, 0.1f, 2.0f, 6.5f, 550.0f, 4.0f };
		Level[3] = SkillStat{ 3, 0.1f, 1.90f, 6.5f, 550.0f, 4.0f };
		Level[4] = SkillStat{ 4, 0.1f, 1.90f, 6.5f, 550.0f, 4.0f };
		Level[5] = SkillStat{ 4, 0.1f, 1.80f, 6.5f, 650.0f, 4.0f };
		Level[6] = SkillStat{ 5, 0.1f, 1.80f, 6.5f, 650.0f, 4.0f };
		Level[7] = SkillStat{ 5, 0.1f, 1.70f, 6.5f, 650.0f, 4.0f };
		Level[8] = SkillStat{ 6, 0.1f, 1.70f, 6.5f, 650.0f, 4.0f };

		AllSkillStat[SkillType::KNIFE] = Level;
	}


	// MAGICWAND
	{
		std::map<int, SkillStat> Level;
		Level[1] = SkillStat{ 2, 0.08f, 2.0f, 10.0f, 500.0f, 4.0f };
		Level[2] = SkillStat{ 3, 0.08f, 2.0f, 10.0f, 500.0f, 4.0f };
		Level[3] = SkillStat{ 3, 0.08f, 1.90f, 10.0f, 500.0f, 4.0f };
		Level[4] = SkillStat{ 4, 0.08f, 1.90f, 10.0f, 500.0f, 4.0f };
		Level[5] = SkillStat{ 4, 0.08f, 1.80f, 10.0f, 500.0f, 4.0f };
		Level[6] = SkillStat{ 5, 0.08f, 1.80f, 10.0f, 500.0f, 4.0f };
		Level[7] = SkillStat{ 5, 0.08f, 1.70f, 10.0f, 500.0f, 4.0f };
		Level[8] = SkillStat{ 6, 0.08f, 1.70f, 10.0f, 500.0f, 4.0f };

		AllSkillStat[SkillType::MAGICWAND] = Level;
	}

	// FIREWAND
	{
		std::map<int, SkillStat> Level;
		Level[1] = SkillStat{ 3, 0.0f, 5.0f, 20.0f, 250.0f, 4.0f };
		Level[2] = SkillStat{ 3, 0.0f, 5.0f, 20.0f, 250.0f, 4.0f };
		Level[3] = SkillStat{ 3, 0.0f, 4.9f, 20.0f, 250.0f, 4.0f };
		Level[4] = SkillStat{ 4, 0.0f, 4.8f, 20.0f, 250.0f, 4.0f };
		Level[5] = SkillStat{ 4, 0.0f, 4.5f, 20.0f, 250.0f, 4.0f };
		Level[6] = SkillStat{ 4, 0.0f, 4.5f, 20.0f, 250.0f, 4.0f };
		Level[7] = SkillStat{ 5, 0.0f, 4.0f, 20.0f, 250.0f, 4.0f };
		Level[8] = SkillStat{ 5, 0.0f, 4.0f, 20.0f, 250.0f, 4.0f };

		AllSkillStat[SkillType::FIREWAND] = Level;
	}



	// THOUSANDEDGE
	{
		std::map<int, SkillStat> Level;
		Level[1] = SkillStat{ 1, 0.1f, 0.0f, 6.5f, 650.0f, 4.0f };
		Level[2] = SkillStat{ 1, 0.1f, 0.0f, 6.5f, 650.0f, 4.0f };
		Level[3] = SkillStat{ 1, 0.1f, 0.0f, 6.5f, 650.0f, 4.0f };
		Level[4] = SkillStat{ 1, 0.1f, 0.0f, 6.5f, 650.0f, 4.0f };
		Level[5] = SkillStat{ 1, 0.1f, 0.0f, 6.5f, 650.0f, 4.0f };
		Level[6] = SkillStat{ 1, 0.1f, 0.0f, 6.5f, 650.0f, 4.0f };
		Level[7] = SkillStat{ 1, 0.1f, 0.0f, 6.5f, 650.0f, 4.0f };
		Level[8] = SkillStat{ 1, 0.1f, 0.0f, 6.5f, 650.0f, 4.0f };

		AllSkillStat[SkillType::THOUSANDEDGE] = Level;
	}

	/// PASSIVE


	return AllSkillStat;
}
