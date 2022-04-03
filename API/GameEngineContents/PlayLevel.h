#pragma once
#include "GameEngine/GameEngineLevel.h"
#include <list>
#include <vector>

class Player;
class Enemy;

// 설명 :
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

	// UI
private:
	std::vector<GameEngineActor*> VecUI_;
	GameEngineActor* ExpUI_;
	GameEngineActor* WeaponUI_;
	GameEngineActor* TimerUI_;
	GameEngineActor* CoinUI_;
	GameEngineActor* LevelUI_;
	GameEngineActor* KillCountUI_;

	

private:
	GameEngineActor*	Map_;
	Player*				Player_;
	float4				PlayerPos_;

	// 큐 로 하면 좋을듯
	Enemy*				Enemy_;
	std::list<Enemy*>	Enemies_;

	void Respawn(int _x, int _y);
	void InfiniteMap();

	
};

