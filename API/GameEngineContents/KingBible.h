#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineMath.h>
#include "GameInfo.h"
#include <map>
#include <vector>
#include "PlayerAttack.h"
#include "Counter.h"

// ���� :
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

	// ȸ��	
	float Range_; // �÷��̾�� å ������ �Ÿ�
	float4 PlayerPos_;
	float DeltaTime_;

	// ��ų ����
	std::map<int, SkillStat> Bible_;
	int Level_;
	int BookCount_;
	float Damage_;

	// ��Ÿ
	bool IsBullet_;
	Counter CoolTimeCounter_;
	Counter DurationCounter_;
	float Alpha_;

	float AlphaDelta_;

};

