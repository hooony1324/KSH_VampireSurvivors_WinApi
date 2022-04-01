#pragma once
#include "Character.h"

// 설명 :
/*
* 게임 진행에 있어서 타이틀->플레이->결과 레벨까지의 플레이어 정보 저장
* < 저장할 정보 >
* - 생존 시간, 획득 골드, 도달 레벨, 처치한 적, 무기(무기레벨, 무기 데미지, 시간, dps)
* - 선택 캐릭터, 획득 무기, 획득 패시브* 
*/
class PlayerInfo
{
private:
	static PlayerInfo* Inst_;

public:
	static PlayerInfo* GetInst()
	{
		return Inst_;
	}

	static void Destroy()
	{
		if (nullptr != Inst_)
		{
			delete Inst_;
			Inst_ = nullptr;
		}
	}

	int SurvivalTime_;
	int EearnedGold_;
	int CharacterLevel_;
	int KillCount_;
	float CurrentExp_;
	float MaxExp_;
	int PlayerLevel_;

	void ChangeCharacter(Character::Type _Type);
	inline Character* GetCharacter()
	{
		return Character_;
	}

private:
	Character* Character_;

private:
	// constrcuter destructer
	PlayerInfo();
	~PlayerInfo();

	// delete Function
	PlayerInfo(const PlayerInfo& _Other) = delete;
	PlayerInfo(PlayerInfo&& _Other) noexcept = delete;
	PlayerInfo& operator=(const PlayerInfo& _Other) = delete;
	PlayerInfo& operator=(PlayerInfo&& _Other) noexcept = delete;

};

