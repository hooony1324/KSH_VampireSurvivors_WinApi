#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class CoinUI : public GameEngineActor
{
public:
	// constrcuter destructer
	CoinUI();
	~CoinUI();

	// delete Function
	CoinUI(const CoinUI& _Other) = delete;
	CoinUI(CoinUI&& _Other) noexcept = delete;
	CoinUI& operator=(const CoinUI& _Other) = delete;
	CoinUI& operator=(CoinUI&& _Other) noexcept = delete;

protected:

	void Start() override;
	void Update() override;
	void Render() override;

private:

};

