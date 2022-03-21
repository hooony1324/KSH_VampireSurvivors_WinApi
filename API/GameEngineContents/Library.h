#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
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

protected:

private:
	virtual void Start();
	virtual void Update();
	virtual void Render();
};

