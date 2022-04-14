#pragma once
#include "GameEngine/GameEngineLevel.h"
#include <list>
#include <vector>
#include <GameEngineBase/GameEngineSound.h>

class Player;
class Enemy;
class EnemyController;
class Library;
class Projectile;
class ProjectileShooter;
class TimerUI;

// ���� :
class GameEngineCollision;
class PlayLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	PlayLevel();
	~PlayLevel();

	// delete Function
	PlayLevel(const PlayLevel& _Other) = delete;
	PlayLevel(PlayLevel&& _Other) noexcept = delete;
	PlayLevel& operator=(const PlayLevel& _Other) = delete;
	PlayLevel& operator=(PlayLevel&& _Other) noexcept = delete;

	

protected:
	void Loading() override;
	void LevelChangeStart() override;
	void Update() override;
	void LevelChangeEnd() override;

private:
	// Sound
	GameEngineSoundPlayer BgmPlayer;


private:
	// UI
	GameEngineActor* ExpUI_;
	GameEngineActor* WeaponUI_;
	TimerUI* TimerUI_;
	GameEngineActor* CoinUI_;
	GameEngineActor* LevelUI_;
	GameEngineActor* KillCountUI_;
	GameEngineActor* PauseUI_;
	GameEngineActor* LevelUpUI_;
	GameEngineActor* StatUI_;
	bool GamePause_;

private:

	// Game
	void GamePause();

	// Map
	void CreateMap();
	void InfiniteMap();

	float				MapLeftX_;
	float				MapRightX_;

	// Enemy
	EnemyController*	EnemyController_;
	Enemy*				Enemy_;
	std::vector<Enemy*>	AllEnemy_;

	// Player
	Library*			Map_;
	Player*				Player_;
	float4				PlayerPos_;


};

