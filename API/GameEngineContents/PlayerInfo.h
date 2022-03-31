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
	float Exp_;

	Character* Character_;
	void ChangeCharacter(Character::Type _Type);

protected:

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

