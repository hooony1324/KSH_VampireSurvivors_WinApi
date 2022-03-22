#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class ResultBackGround : public GameEngineActor
{
public:
	// constrcuter destructer
	ResultBackGround();
	~ResultBackGround();

	// delete Function
	ResultBackGround(const ResultBackGround& _Other) = delete;
	ResultBackGround(ResultBackGround&& _Other) noexcept = delete;
	ResultBackGround& operator=(const ResultBackGround& _Other) = delete;
	ResultBackGround& operator=(ResultBackGround&& _Other) noexcept = delete;

protected:

	void Start() override;
	void Update() override;
	void Render() override;

private:

};

