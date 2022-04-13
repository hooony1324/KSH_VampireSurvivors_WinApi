#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include "Character.h"
#include <vector>




// ���� :
class GameInfo
{
public:
	class PlayerInfo
	{
	public:
		float4 PlayerPos_;

		float MaxExp_;
		float CurrentExp_;
		int MaxLevel_;
		int	Level_;

		int SurvivalTime_;
		int EearnedCoin_;
		int KillCount_;

		// �нú� �⺻ �ɷ�ġ (ü��, ���ǵ�, ���ݷ�, ...)
		float Speed_;			// �̵��ӵ�
		float CurrentHp_;		// ü��
		float MaxHp_;
		float Recovery_;		// ü�� ���
		float Guard_;			// ����
		float Power_;			// �߰� ������, ����
		float MeleeRange_;		// ���� ���� ����(����, ����, ����, ���� �� ���� ���ݸ� �ش�)
		float ShootSpeedRatio_;	// ��ü ����ü �ӵ� ��������
		float AddShootNum_;		// ����ü ��
		float Duration_;		// ��ų ���ӽð�

		// �нú� ���� �ɷ�ġ
		float Luck_;			// ������ Ȯ�� 3�� -> 4��
		float Growth_;			// ����ġ ȹ��� �߰� ����ġ
		float Greed_;			// �� ȹ��� �߰� ��
		float Magnet_;			// ������ ȹ�� ����
		int	Revival_;			// ��Ȱ Ƚ��

		// ���� ����

	};

public:
	static void Destroy()
	{
		if (nullptr != Character_)
		{
			delete Character_;
			Character_ = nullptr;
		}

		if (nullptr != PlayerInfo_)
		{
			delete PlayerInfo_;
			PlayerInfo_ = nullptr;
		}
	}

	static void SetCharacter(CharacterType _CharacterType)
	{
		if (nullptr != Character_)
		{
			delete Character_;
		}
		Character_ = new Character(_CharacterType);
	}

	static Character* GetCharacter()
	{
		return Character_;
	}

	static PlayerInfo* GetPlayerInfo()
	{
		return PlayerInfo_;
	}

	static void SetPlayerInfo();

private:
	// ��� ������Ʈ �Ǿ� �Ǵ� ����, UI�� ǥ���� ����
	static Character* Character_;	// ĳ���� ���� ����
	static PlayerInfo* PlayerInfo_;	// �ΰ��� �÷��̾� ����


private:
	// constrcuter destructer
	GameInfo();
	~GameInfo();

	// delete Function
	GameInfo(const GameInfo& _Other) = delete;
	GameInfo(GameInfo&& _Other) noexcept = delete;
	GameInfo& operator=(const GameInfo& _Other) = delete;
	GameInfo& operator=(GameInfo&& _Other) noexcept = delete;
};


