#pragma once
#include <GameEngine/GameEngineActor.h>

// 설명 : 
class Character;
class GameEngineImage;
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
	float Gravity_;
	float AccGravity_;
	GameEngineImage* MapColImage_;

	void Start() override;
	void Update() override;
	void Render() override;


// 내가 추가한 내용
private:
	Character*			PlayerStat_;
	float4				PlayerPos_;
	float4				MoveDir_;
	float4				HeadDir_;

	GameEngineRenderer* PlayerRenderer_;
	GameEngineRenderer* Hp_BarRed_;
	float4				Hp_BarSize_;
	float4				Hp_BarPivot_;

	void KillPlayer();
	void HpBarRender();
};

