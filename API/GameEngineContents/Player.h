#pragma once
#include <GameEngine/GameEngineActor.h>
#include <vector>

// 설명 : 
class Character;
class GameEngineImage;
class Projectile;
class GameEngineCollision;
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

private:
	/*float Gravity_;
	float AccGravity_;
	GameEngineImage* MapColImage_;*/

	void Start() override;
	void Update() override;
	void Render() override;
private:

	void SetGameInfo();
	Character*				CharacterStat_;
	float4					PlayerPos_;
	float4					MoveDir_;
	int						HeadDir_;
	bool					Hitable_; // 플레이어 무적여부
	float					InvincibleTime_;
	float					HitTime_;	// 피격시 무적시간
	float					Speed_;

	GameEngineCollision*	PlayerCol_;
	GameEngineRenderer*		PlayerRenderer_;
	GameEngineRenderer*		Hp_BarRed_;
	float4					Hp_BarSize_;

	void PlayerMove();
	void HpBarRender();


	// 플레이어 피격
	void MonsterAttPlayer();
	void Attacked(int _Damage);

	// 공격
	GameEngineCollision* PlayerAttRange_;

	// 모든 충돌 체크
	void AllCollisionCheck();


	
};

