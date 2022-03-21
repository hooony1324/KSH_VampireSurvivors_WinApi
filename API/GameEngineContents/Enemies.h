#pragma once
#include <GameEngine/GameEngineActor.h>

// ���� : 
class Enemies : public GameEngineActor
{
public:
	// constrcuter destructer
	Enemies();
	~Enemies();

	// delete Function
	Enemies(const Enemies& _Other) = delete;
	Enemies(Enemies&& _Other) noexcept = delete;
	Enemies& operator=(const Enemies& _Other) = delete;
	Enemies& operator=(Enemies&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Render() override;
};

