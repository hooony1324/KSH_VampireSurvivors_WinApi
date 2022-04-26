#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class GameEngineRenderer;
class Intro : public GameEngineActor
{
public:
	// constrcuter destructer
	Intro();
	~Intro();

	// delete Function
	Intro(const Intro& _Other) = delete;
	Intro(Intro&& _Other) noexcept = delete;
	Intro& operator=(const Intro& _Other) = delete;
	Intro& operator=(Intro&& _Other) noexcept = delete;

	bool IsCautionOut();

protected:

	void Start() override;
	void Update() override;
	void Render() override;

private:
	GameEngineRenderer* Renderer_;
	bool IntroSoundPlay_;
};

