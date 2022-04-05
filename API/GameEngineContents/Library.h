#pragma once
#include <GameEngine/GameEngineActor.h>
#include <vector>

// 설명 :
class GameEngineCollision;
class Library : public GameEngineActor
{
public:
	// constrcuter destructer
	Library();
	~Library();

	// delete Function
	Library(const Library& _Other) = delete;
	Library(Library&& _Other) noexcept = delete;
	Library& operator=(const Library& _Other) = delete;
	Library& operator=(Library&& _Other) noexcept = delete;

	void Test()
	{}

protected:

private:
	virtual void Start();
	virtual void Update();
	virtual void Render();

	GameEngineRenderer* Map_;
	float				MapLeftX_;
	float				MapRightX_;
	
	GameEngineCollision* MapWallTop_;
	GameEngineCollision* MapWallBot_;
	std::vector<GameEngineCollision*> BumpedPlayer_; // 맵의 위 아래 충돌

	GameEngineCollision* MapEndLeft_;
	GameEngineCollision* MapEndRight_;


	// 플레이어 맵 위, 아래에서 막음
	void PlayerBlock();
};

