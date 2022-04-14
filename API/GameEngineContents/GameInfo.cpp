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
	PlayerInfo_->ShootSpeedRatio_	= Character_->ShootSpeedRatio_;
	PlayerInfo_->AddShootNum_		= Character_->AddShootNum_;
	PlayerInfo_->Duration_			= Character_->Duration_;
	PlayerInfo_->Luck_				= Character_->Luck_;
	PlayerInfo_->Growth_			= Character_->Growth_;
	PlayerInfo_->Greed_				= Character_->Greed_;
	PlayerInfo_->Magnet_			= Character_->Magnet_;
	PlayerInfo_->Revival_			= Character_->Revival_;


}
