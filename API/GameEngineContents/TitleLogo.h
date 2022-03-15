#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class TitleLogo : public GameEngineActor
{
public:
	// constrcuter destructer
	TitleLogo();
	~TitleLogo();

	// delete Function
	TitleLogo(const TitleLogo& _Other) = delete;
	TitleLogo(TitleLogo&& _Other) noexcept = delete;
	TitleLogo& operator=(const TitleLogo& _Other) = delete;
	TitleLogo& operator=(TitleLogo&& _Other) noexcept = delete;

protected:
	void Start();
	void Render();

private:

};

