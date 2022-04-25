#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFont.h>

// Ό³Έν :
class KillCountUI : public GameEngineActor
{
public:
	// constrcuter destructer
	KillCountUI();
	~KillCountUI();

	// delete Function
	KillCountUI(const KillCountUI& _Other) = delete;
	KillCountUI(KillCountUI&& _Other) noexcept = delete;
	KillCountUI& operator=(const KillCountUI& _Other) = delete;
	KillCountUI& operator=(KillCountUI&& _Other) noexcept = delete;

protected:

	void Start() override;
	void Update() override;
	void Render() override;

private:
	GameEngineFont TextFont_;


};

