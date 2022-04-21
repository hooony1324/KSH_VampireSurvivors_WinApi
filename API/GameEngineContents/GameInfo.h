#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include "Character.h"
#include <vector>
#include <map>
#include "GameEnum.h"


// 설명 :
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

		// 패시브 기본 능력치 (체력, 스피드, 공격력, ...)
		float Speed_;			// 이동속도
		float CurrentHp_;		// 체력
		float MaxHp_;
		float Recovery_;		// 체력 재생
		float Guard_;			// 방어력
		float Power_;			// 추가 데미지, 괴력
		float MeleeRange_;		// 근접 공격 범위(성서, 마늘, 성수, 번개 등 범위 공격만 해당)
		float ShootSpeedRatio_;	// 전체 투사체 속도 증가비율
		float AddShootNum_;		// 투사체 수
		float Duration_;		// 스킬 지속시간

		// 패시브 서브 능력치
		float Luck_;			// 아이템 확률 3개 -> 4개
		float Growth_;			// 경험치 획득시 추가 경험치
		float Greed_;			// 돈 획득시 추가 돈
		float Magnet_;			// 아이템 획득 범위
		int	Revival_;			// 부활 횟수

		// 무기 정보, 12개만 장착 가능
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
	// 계속 업데이트 되야 되는 정보, UI에 표시할 정보
	static Character* Character_;	// 캐릭터 선택 정보
	static PlayerInfo* PlayerInfo_;	// 인게임 플레이어 정보
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
	"Knife", "MagicWand", "FireWand", "Clover"
};

//"Knife", "MagicWand", "FireWand", "Runetracer",
//"Axe", "Clocklancet", "Cross", "Bible",
//"Whip", "Garlic", "Laurel", "Lightening",
//"Holywater", "FiveStar", "Bracer", "Emptytome",
//"Spinach", "Spellbinder", "Hollowheart", "Clover",
//"Pummarola", "Candle", "Wing"