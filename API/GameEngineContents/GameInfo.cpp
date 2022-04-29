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
	PlayerInfo_->ShootSpeedRatio_	= Character_->ShootSpeedRatio_;
	PlayerInfo_->AddShootNum_		= Character_->AddShootNum_;
	PlayerInfo_->Duration_			= Character_->Duration_;
	PlayerInfo_->CoolTime_			= Character_->CoolTime_;

	PlayerInfo_->Luck_				= Character_->Luck_;
	PlayerInfo_->Growth_			= Character_->Growth_;
	PlayerInfo_->Greed_				= Character_->Greed_;
	PlayerInfo_->Magnet_			= Character_->Magnet_;
	PlayerInfo_->Revival_			= Character_->Revival_;

	// 초기화
	PlayerInfo_->ActiveSkillSlot_.clear();
	PlayerInfo_->PassiveSkillSlot_.clear();

	for (int i = 0; i < static_cast<int>(SkillType::MAX); i++)
	{
		PlayerInfo_->SkillLevelInfo_[i] = 0;
	}


	// 기본 스킬 입력
	PlayerInfo_->ActiveSkillSlot_.push_back(Character_->BaseSkill_);
	PlayerInfo_->SkillLevelInfo_[static_cast<int>(Character_->BaseSkill_)] = 1;

}

bool GameInfo::SkillLevelFull()
{
	for (int i = 0; i < static_cast<int>(SkillType::MAX); i++)
	{
		if (PlayerInfo_->SkillLevelInfo_[i] < SKILL_LEVELMAX)
		{
			return false;
		}
	}

	return true;
	
}
