#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineMath.h>
#include "GameInfo.h"
#include <map>
#include <vector>
#include "PlayerAttack.h"
#include "Counter.h"

// 설명 :
class GameEngineRenderer;
class GameEngineCollision;
class KingBible : public PlayerAttack
{
private:
	enum class STATE
	{
		NONE,
		SPIN,
		VANISH,
	};

	class Bible
	{
	public:
		GameEngineRenderer* BookRenderer_;
		GameEngineCollision* BookCollision_;

		void SetRCPivot(float4 _Pivot);
	};

public:
	// constrcuter destructer
	KingBible();
	~KingBible();

	// delete Function
	KingBible(const KingBible& _Other) = delete;
	KingBible(KingBible&& _Other) noexcept = delete;
	KingBible& operator=(const KingBible& _Other) = delete;
	KingBible& operator=(KingBible&& _Other) noexcept = delete;

	float GetDamage() override
	{
		return Damage_;
	}

	void SetDamage(float _Damage) override
	{
		Damage_ = _Damage;
	}

	bool IsBullet() override
	{
		return IsBullet_;
	}

protected:

	void Start() override;
	void Update() override;

private:
	STATE State_;
	void StateUpdate();
	void ChangeState(STATE _State);

	void SpinStart();
	void SpinUpdate();

	void VanishStart();
	void VanishUpdate();

private:

	std::vector<Bible> Bibles_;

	// 회전	
	float Range_; // 플레이어와 책 사이의 거리
	float4 PlayerPos_;
	float DeltaTime_;

	// 스킬 정보
	std::map<int, SkillStat> Bible_;
	int Level_;
	int BookCount_;
	float Damage_;

	// 기타
	bool IsBullet_;
	Counter CoolTimeCounter_;
	Counter DurationCounter_;
	float Alpha_;

	float AlphaDelta_;

};

