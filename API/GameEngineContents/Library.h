#pragma once
#include <GameEngine/GameEngineActor.h>
#include <vector>

// ���� :
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
	std::vector<GameEngineCollision*> BumpedPlayer_; // ���� �� �Ʒ� �浹

	GameEngineCollision* MapEndLeft_;
	GameEngineCollision* MapEndRight_;


	// �÷��̾� �� ��, �Ʒ����� ����
	void PlayerBlock();
};

