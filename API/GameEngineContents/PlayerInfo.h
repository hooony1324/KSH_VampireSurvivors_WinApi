#pragma once
#include "Character.h"

// ���� :
/*
* ���� ���࿡ �־ Ÿ��Ʋ->�÷���->��� ���������� �÷��̾� ���� ����
* < ������ ���� >
* - ���� �ð�, ȹ�� ���, ���� ����, óġ�� ��, ����(���ⷹ��, ���� ������, �ð�, dps)
* - ���� ĳ����, ȹ�� ����, ȹ�� �нú�* 
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

