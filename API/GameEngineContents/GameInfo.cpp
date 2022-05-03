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
		MsgBoxAssert("ĳ���Ͱ� ���õ��� ����ä�� ������ ���۵Ǿ����ϴ�");
	}

	// ����ġ
	PlayerInfo_->MaxExp_ = 100;
	PlayerInfo_->CurrentExp_ = 0;
	PlayerInfo_->MaxLevel_ = 200;
	PlayerInfo_->Level_ = 1;

	// �����ð�
	PlayerInfo_->SurvivalTime_ = 0;

	// ȹ�� ���
	PlayerInfo_->EearnedCoin_ = 0;

	// �� ó�� ��
	PlayerInfo_->KillCount_ = 0;

	// PlayerInfo <- CharacterInfo �޾ƿ���
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

	// �ʱ�ȭ
	PlayerInfo_->ActiveSkillSlot_.clear();
	PlayerInfo_->PassiveSkillSlot_.clear();

	// ��� ��ų ���� ���� �ʱ�ȭ
	for (int i = 0; i < EVOLVE_MAX; i++)
	{
		SkillType Type = static_cast<SkillType>(i);
		PlayerInfo_->AllSkillLevel_[Type] = 0;
	}

	// �⺻ ��ų �Է�
	PlayerInfo_->ActiveSkillSlot_.push_back(Character_->BaseSkill_);

	// �⺻��ų ���� �Է�
	PlayerInfo_->AllSkillLevel_[Character_->BaseSkill_] = 1;

}

bool GameInfo::SkillLevelFull()
{

	std::map<SkillType, int> AllSkillLevel = PlayerInfo_->AllSkillLevel_;

	for (int i = 0; i < static_cast<int>(PlayerInfo_->ActiveSkillSlot_.size()); i++)
	{
		if (SKILL_LEVELMAX > AllSkillLevel[PlayerInfo_->ActiveSkillSlot_[i]])
		{
			// ���� Ÿ���� ��ŵ
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
	// ��Ƽ�� ���Կ��� 8���� ��Ƽ�꽺ų ���� Ȯ��
	SkillType MaxLevelActiveSkill = SkillType::NONE;
	for (int i = 0; i < static_cast<int>(PlayerInfo_->ActiveSkillSlot_.size()); i++)
	{
		if (8 <= PlayerInfo_->AllSkillLevel_[PlayerInfo_->ActiveSkillSlot_[i]])
		{
			MaxLevelActiveSkill = PlayerInfo_->ActiveSkillSlot_[i];

			// �� ��ų�� ��� �нú� 8���� Ȯ��
			SkillType Combination = CombinationSkill(MaxLevelActiveSkill);
			if (8 == PlayerInfo_->AllSkillLevel_[Combination])
			{
				// ���� Ȯ�ε� ���� ��ų ����
				return ChangeSkill(MaxLevelActiveSkill);
			}
		}
	}

	return SkillType::NONE;
}

// ��Ƽ���� ���տ� �нú� ��ų ��ȯ
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

// ��Ƽ�� ��ų -> ������ų  | ������ų -> ��Ƽ�꽺ų
SkillType GameInfo::ChangeSkill(SkillType _Type)
{
	switch (_Type)
	{
	// ��Ƽ��
	case SkillType::KNIFE:
		return SkillType::THOUSANDEDGE;
		break;

	// ����
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

	// ActiveSlot�� �ε��� ã�Ƴ���
	for (int i = 0; i < static_cast<int>(PlayerInfo_->ActiveSkillSlot_.size()); i++)
	{
		if (ActiveSkill == PlayerInfo_->ActiveSkillSlot_[i])
		{
			// ���� ��ų ����
			PlayerInfo_->AllSkillLevel_[ActiveSkill] = -1;

			// ���� ��ų
			PlayerInfo_->ActiveSkillSlot_[i] = _EvolvedType;
			PlayerInfo_->AllSkillLevel_[_EvolvedType] = 1;
		}
	}

}


// 	std::map<SkillType, std::map<int, SkillStat>> AllSkillStat_;
std::map<SkillType, std::map<int, SkillStat>> GameInfo::SetAllSkillStat()
{
	std::map<SkillType, std::map<int, SkillStat>> AllSkillStat;

	// ź��		���͹�		��Ÿ��		������		�ӵ�			���ӽð� 
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
