#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineBase/GameEngineDebug.h>
#include "Character.h"
#include <vector>
#include <map>
#include "GameEnum.h"

static GameEngineRandom Random;


class SkillStat
{
public:
	//ź��		���͹�		��Ÿ��		������		�ӵ�			���ӽð� 
	int SkillCount_;
	float Interval_;
	float CoolTime_;
	float Damage_;
	float Speed_;
	float Duration_;
};

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
		float MaxHp_;
		float CurrentHp_;		// ü��
		float Speed_;			// �̵��ӵ�
		float Recovery_;		// ü�� ���
		float Guard_;			// ����
		float Power_;			// �߰� ������, ����
		float MeleeRange_;		// ���� ���� ����(����, ����, ����, ���� �� ���� ���ݸ� �ش�)
		float ShootSpeedRatio_;	// ��ü ����ü �ӵ� ��������
		float Duration_;		// ��ų ���ӽð�
		float AddShootNum_;		// ����ü ��
		float CoolTime_;

		// �нú� ���� �ɷ�ġ
		float Luck_;			// ������ Ȯ�� 3�� -> 4��
		float Growth_;			// ����ġ ȹ��� �߰� ����ġ
		float Greed_;			// �� ȹ��� �߰� ��
		float Magnet_;			// ������ ȹ�� ����
		int	Revival_;			// ��Ȱ Ƚ��

		// ��ų ����, 12���� ���� ����
		std::vector<SkillType> ActiveSkillSlot_;
		std::vector<SkillType> PassiveSkillSlot_;

		// ��ų ���� ����
		std::map<SkillType, int> AllSkillLevel_;
	};

	static bool SkillLevelFull();
	static SkillType SkillEvolveCheck();
	static void PushEvolvedSkill(SkillType _EvolvedType);

	// Type | Level(1~8) | Stat(6��)
	static std::map<SkillType, std::map<int, SkillStat>> AllSkillStat_;
	static std::map<SkillType, std::map<int, SkillStat>> SetAllSkillStat();

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

	static SkillType CombinationSkill(SkillType _Type);
	static SkillType ChangeSkill(SkillType _Type);
	
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

static std::string SkillTypeToName(SkillType _SkillType)
{
	switch (_SkillType)
	{
	case SkillType::KNIFE:
		return "Knife";
		break;
	case SkillType::MAGICWAND:
		return "MagicWand";
		break;
	case SkillType::FIREWAND:
		return "FireWand";
		break;
	case SkillType::BRACER:
		return "Bracer";
		break;
	case SkillType::CLOVER:
		return "Clover";
		break;
	case SkillType::THOUSANDEDGE:
		return "ThousandEdge";
		break;
	case SkillType::NONE:
		return "None";
		break;
	default:
		break;
	}

	return "None";
}

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

