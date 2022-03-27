#pragma once
#include <GameEngine/GameEngineActor.h>

// 설명 : 
class Character;
class Player : public GameEngineActor
{
public:
	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	void SetCharacter(Character _Type);
protected:

private:
	void Start() override;
	void Update() override;
	void Render() override;

	// 기본 능력치 (체력, 스피드, 공격력, ...)
	float Speed_;			// 이동속도
	float Hp_;				// 체력
	float Recovery_;		// 체력 재생
	float Guard_;			// 방어력
	float Power_;			// 괴력
	float Range_;			// 공격 범위(성서, 마늘, 성수, 번개 등 범위 공격만 해당)
	float ShootSpeed_;		// 투사체 속도
	float ShootNum_;		// 투사체 수
	float Duration_;		// 스킬 지속시간


	// 패시브
	float Luck_;			// 아이템 확률 3개 -> 4개
	float Growth_;			// 경험치 획득시 추가 경험치
	float Greed_;			// 돈 획득시 추가 돈
	float Magnet_;			// 아이템 획득 범위

	int Revival_;			// 부활 횟수

};

