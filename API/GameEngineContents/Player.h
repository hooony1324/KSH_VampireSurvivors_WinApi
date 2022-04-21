#pragma once
#include <GameEngine/GameEngineActor.h>
#include <vector>


// 설명 : 
class Character;
class GameEngineImage;
class ProjectileShooter;
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
	enum class HeadDir
	{
		LEFT,
		RIGHT
	};

	void SetGameInfo();

	Character*				CharacterStat_;
	float4					PlayerPos_;
	float4					MoveDir_;
	float4					Hp_BarSize_;
	HeadDir					HeadDir_;
	bool					Hitable_; // 플레이어 무적여부
	float					InvincibleTime_;
	float					HitTime_;	// 피격시 무적시간
	float					Speed_;

	GameEngineCollision*	PlayerCol_;
	GameEngineCollision*	PlayerShootRange_;
	std::vector<GameEngineCollision*>	ShootableEnemy_;

	// 렌더
	GameEngineRenderer*		PlayerRenderer_;
	GameEngineRenderer*		Hp_BarRed_;

	void PlayerMove();
	void HpBarRender();
	void Attacked(int _Damage);

	// 충돌 체크
	void AllCollisionCheck();
	float MapColCheck(float _PlayerSpeed);
	void MonsterAttackCheck();
	float4 ShootableEnemeyCheck();

	GameEngineImage* MapColImage_;

	// 슈팅
	void Shooting();

	// 배열로 바꿀 예정
	ProjectileShooter* MagicShooter_;
	ProjectileShooter* KnifeShooter_;
	ProjectileShooter* FireShooter_;
	ProjectileShooter* RuneShooter_;

	
};

