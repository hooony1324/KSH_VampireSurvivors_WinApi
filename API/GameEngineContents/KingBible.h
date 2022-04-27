#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class KingBible : public GameEngineActor
{
public:
	// constrcuter destructer
	KingBible();
	~KingBible();

	// delete Function
	KingBible(const KingBible& _Other) = delete;
	KingBible(KingBible&& _Other) noexcept = delete;
	KingBible& operator=(const KingBible& _Other) = delete;
	KingBible& operator=(KingBible&& _Other) noexcept = delete;

protected:

	void Start() override;
	void Update() override;
	void Render() override;

private:

};

