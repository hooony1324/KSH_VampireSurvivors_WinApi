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
class GameEngineCollision;
class GameEngineImage;
class PlayLevel : public GameEngineLevel
{
public:
	enum class LevelState
	{
		PLAY,
		LEVELUP,
		PAUSE
	};

public:
	// constrcuter destructer
	PlayLevel();
	~PlayLevel();

	// delete Function
	PlayLevel(const PlayLevel& _Other) = delete;
	PlayLevel(PlayLevel&& _Other) noexcept = delete;
	PlayLevel& operator=(const PlayLevel& _Other) = delete;
	PlayLevel& operator=(PlayLevel&& _Other) noexcept = delete;

	static GameEngineImage* MapColImage_;

protected:
	void Loading() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void Update() override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:
	// Sound
	GameEngineSoundPlayer BgmPlayer;

	// FSM
	void UpdateState();
	void ChangeState(LevelState _State);

	void PlayStart();
	void LevelUpStart();
	void PauseStart();

	void PlayUpdate();
	void LevelUpUpdate();
	void PauseUpdate();

	LevelState LevelState_;

private:
	// UI
	GameEngineActor* ExpUI_;
	GameEngineActor* WeaponUI_;
	GameEngineActor* TimerUI_;
	GameEngineActor* CoinUI_;
	GameEngineActor* LevelUI_;
	GameEngineActor* KillCountUI_;
	GameEngineActor* PauseUI_;
	GameEngineActor* StatUI_;


private:
	// Game
	void GamePause();
	void ShowPauseMenu();
	void LevelUpUICheck();

	// Map
	void CreateMap();
	void InfiniteMap();

	float				MapLeftX_;
	float				MapRightX_;

	// Enemy
	EnemyController*	EnemyController_;

	// Player
	Library*			Map_;
	Player*				Player_;
	float4				PlayerPos_;


};

