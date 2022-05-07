#pragma once
#include <GameEngine/GameEngineActor.h>
#include <vector>

// Ό³Έν :
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

	float4 GetRendererScale();
	void CheckPlayerOnEnd();

	

private:
	bool ShowColMap_;


private:
	virtual void Start();
	virtual void Update();
	virtual void Render();

	GameEngineRenderer* Map_;
	GameEngineRenderer* ColMap_;
	float TelePortX_;

	GameEngineCollision* MapEndLeft_;
	GameEngineCollision* MapEndRight_;

};

