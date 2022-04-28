#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include "Character.h"
#include <vector>
#include <map>
#include "GameEnum.h"
#include <GameEngineBase/GameEngineRandom.h>

static GameEngineRandom Random;

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

		// ���� ����, 12���� ���� ����
		std::vector<SkillType> ActiveSkillSlot_;
		std::vector<SkillType> PassiveSkillSlot_;
		int SkillLevelInfo_[static_cast<int>(SkillType::MAX)];

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

	static bool IsPause()
	{
		return Pause_;
	}

	static void SetPause(bool _Value)
	{
		Pause_ = _Value;
	}

private:
	// ��� ������Ʈ �Ǿ� �Ǵ� ����, UI�� ǥ���� ����
	static Character* Character_;	// ĳ���� ���� ����
	static PlayerInfo* PlayerInfo_;	// �ΰ��� �÷��̾� ����
	static bool Pause_;

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

static std::string SkillOrder[] =
{
	"Knife", "MagicWand", "FireWand", "Bracer", "Clover", 
};

//"Knife", "MagicWand", "FireWand", "Runetracer",
//"Axe", "Clocklancet", "Cross", "Bible",
//"Whip", "Garlic", "Laurel", "Lightening",
//"Holywater", "FiveStar", "Bracer", "Emptytome",
//"Spinach", "Spellbinder", "Hollowheart", "Clover",
//"Pummarola", "Candle", "Wing"


// Character.h �� CharacterType�� ������ ���� ����
static std::string CharacterNameList[] =
{
	"Imelda", "Cavallo", "Poe"
};