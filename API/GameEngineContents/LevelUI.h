#pragma once
#include <Windows.h>
#include <GameEngine/GameEngineActor.h>
#include <vector>

// Ό³Έν :

class GameEngineRenderer;
class LevelUI : public GameEngineActor
{
public:
	// constrcuter destructer
	LevelUI();
	~LevelUI();

	// delete Function
	LevelUI(const LevelUI& _Other) = delete;
	LevelUI(LevelUI&& _Other) noexcept = delete;
	LevelUI& operator=(const LevelUI& _Other) = delete;
	LevelUI& operator=(LevelUI&& _Other) noexcept = delete;

protected:

	void Start() override;
	void Update() override;
	void Render() override;

private:


	std::vector<GameEngineRenderer*> Numbers_;
	GameEngineRenderer* Number1_;
	GameEngineRenderer* Number2_;
	GameEngineRenderer* Number3_;

	int PlayerLevel_;
	HDC BackBufferDC_;

};

