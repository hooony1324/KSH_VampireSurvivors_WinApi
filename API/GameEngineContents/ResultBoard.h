#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class Arrow;
class ResultBoard : public GameEngineActor
{
public:
	// constrcuter destructer
	ResultBoard();
	~ResultBoard();

	// delete Function
	ResultBoard(const ResultBoard& _Other) = delete;
	ResultBoard(ResultBoard&& _Other) noexcept = delete;
	ResultBoard& operator=(const ResultBoard& _Other) = delete;
	ResultBoard& operator=(ResultBoard&& _Other) noexcept = delete;

protected:

	void Start() override;
	void Update() override;
	void Render() override;

private:
	Arrow* ArrowPtr_;
	GameEngineRenderer* ButtonConfirm_;
};

