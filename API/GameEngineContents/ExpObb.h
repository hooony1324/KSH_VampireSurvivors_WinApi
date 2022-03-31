#pragma once
#include <GameEngine/GameEngineActor.h>

// ���� :
class ExpObb : public GameEngineActor
{
public:
	// constrcuter destructer
	ExpObb();
	~ExpObb();

	// delete Function
	ExpObb(const ExpObb& _Other) = delete;
	ExpObb(ExpObb&& _Other) noexcept = delete;
	ExpObb& operator=(const ExpObb& _Other) = delete;
	ExpObb& operator=(ExpObb&& _Other) noexcept = delete;

protected:

	void Start() override;
	void Update() override;
	void Render() override;

private:

};

