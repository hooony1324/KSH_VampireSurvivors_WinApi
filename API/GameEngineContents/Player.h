#pragma once
#include <GameEngine/GameEngineActor.h>
#include <vector>

// ���� : 
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
	bool					Hitable_; // �÷��̾� ��������
	float					InvincibleTime_;
	float					HitTime_;	// �ǰݽ� �����ð�
	float					Speed_;

	GameEngineCollision*	PlayerCol_;
	GameEngineRenderer*		PlayerRenderer_;
	GameEngineRenderer*		Hp_BarRed_;
	float4					Hp_BarSize_;

	void PlayerMove();
	void HpBarRender();


	// �÷��̾� �ǰ�
	void MonsterAttPlayer();
	void Attacked(int _Damage);

	// ����
	GameEngineCollision* PlayerAttRange_;

	// ��� �浹 üũ
	void AllCollisionCheck();


	
};

