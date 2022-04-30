#include "GameInfo.h"
#include <GameEngineBase/GameEngineDebug.h>

Character* GameInfo::Character_ = nullptr;
GameInfo::PlayerInfo* GameInfo::PlayerInfo_ = new PlayerInfo();
bool GameInfo::Pause_ = false;

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

	//for (int i = 0; i < static_cast<int>(SkillType::MAX); i++)
	//{
	//	PlayerInfo_->SkillLevelInfo_[i] = 0;
	//}


	// �⺻ ��ų �Է�
	PlayerInfo_->ActiveSkillSlot_.push_back(Character_->BaseSkill_);
	//PlayerInfo_->SkillLevelInfo_[static_cast<int>(Character_->BaseSkill_)] = 1;


	// �ʱ�ȭ : ��
	for (int i = 0; i < static_cast<int>(SkillType::MAX); i++)
	{
		SkillType Type = static_cast<SkillType>(i);
		PlayerInfo_->AllSkillLevel_[Type] = 0;
	}
	// �⺻��ų �Է� : ��
	PlayerInfo_->AllSkillLevel_[Character_->BaseSkill_] = 1;



}

bool GameInfo::SkillLevelFull()
{
	//for (int i = 0; i < static_cast<int>(SkillType::MAX); i++)
	//{
	//	if (PlayerInfo_->SkillLevelInfo_[i] < SKILL_LEVELMAX)
	//	{
	//		return false;
	//	}
	//}

	// �ϳ��� 8���� �̸� ��ų ������ HP/MONEY �ڽ� ����� ����
	std::map<SkillType, int>::iterator FindIter = PlayerInfo_->AllSkillLevel_.begin();
	std::map<SkillType, int>::iterator EndIter = PlayerInfo_->AllSkillLevel_.end();

	for (; FindIter != EndIter; ++FindIter)
	{
		if ((*FindIter).second < SKILL_LEVELMAX)
		{
			return false;
		}
	}

	return true;
}

SkillType GameInfo::SkillEvolveCheck()
{
	// ��Ƽ�� ���Կ��� 8���� ��Ƽ�꽺ųȮ��
	SkillType MaxLevelActiveSkill = SkillType::NONE;
	for (int i = 0; i < static_cast<int>(PlayerInfo_->ActiveSkillSlot_.size()); i++)
	{
		if (8 <= PlayerInfo_->AllSkillLevel_[PlayerInfo_->ActiveSkillSlot_[i]])
		{
			MaxLevelActiveSkill = PlayerInfo_->ActiveSkillSlot_[i];
			break;
		}
	}

	// 8���� ������
	if (MaxLevelActiveSkill == SkillType::NONE)
	{
		return MaxLevelActiveSkill;
	}

	// �� ��ų�� ��� �нú� 8���� Ȯ��
	SkillType Combination = CombinationSkill(MaxLevelActiveSkill);

	if (8 == PlayerInfo_->AllSkillLevel_[Combination])
	{
		// ���� ��ų ����
		return ChangeSkill(Combination);
	}

	return SkillType::NONE;

}

SkillType GameInfo::CombinationSkill(SkillType _Type)
{
	switch (_Type)
	{
	case SkillType::KNIFE:
		return SkillType::BRACER;
		break;
	}
}

SkillType GameInfo::ChangeSkill(SkillType _Type)
{
	switch (_Type)
	{
	case SkillType::BRACER:
		return SkillType::THOUSANDEDGE;
		break;
	case SkillType::THOUSANDEDGE:
		return SkillType::KNIFE;
		break;
	}
}

void GameInfo::ChangeEvolvedSkill(SkillType _EvolvedType)
{
	SkillType BeforeType = ChangeSkill(_EvolvedType);

	for (int i = 0; i < static_cast<int>(PlayerInfo_->ActiveSkillSlot_.size()); i++)
	{
		if (BeforeType == PlayerInfo_->ActiveSkillSlot_[i])
		{
			// �� �ε��� ��ġ�� �������� ����
			PlayerInfo_->ActiveSkillSlot_[i] = _EvolvedType;
			PlayerInfo_->AllSkillLevel_[_EvolvedType] = 1;
			return;
		}
	}

	
}

