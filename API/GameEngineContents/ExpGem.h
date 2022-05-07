#include <GameEngine/GameEngineActor.h>
#include "Counter.h"

enum class GemType
{
	GREEN,
	BLUE,
	RED
};


// 설명 :
class GameEngineCollision;
class ExpGem : public GameEngineActor
{
private:
	enum class STATE
	{
		IDLE,
		MOVEOUT,
		MOVEIN,
	};

public:
	// constrcuter destructer
	ExpGem();
	~ExpGem();

	// delete Function
	ExpGem(const ExpGem& _Other) = delete;
	ExpGem(ExpGem&& _Other) noexcept = delete;
	ExpGem& operator=(const ExpGem& _Other) = delete;
	ExpGem& operator=(ExpGem&& _Other) noexcept = delete;

	inline float GetExp()
	{
		return Exp_;
	}

	void SetType(GemType _Type);

private:
	STATE State_;
	void StateUpdate();
	void ChangeState(STATE _State);

	void IdleUpdate();
	void MoveOutUpdate();
	void MoveInUpdate();

protected:
	void Start() override;
	void Update() override;

private:

	void PlayerCheck();

	static float RedExp_;

	GameEngineRenderer* Renderer_;
	GameEngineCollision* Col_;
	float Exp_;
	GemType Type_;

	// 플레이어 상호작용
	float DeltaTime_;
	float4 PlayerPos_;
	float4 Pos_;
	float4 MoveDir_;
	bool Get_;
	float SumDeltaTime_;
	Counter MoveOutCounter_;
	float MoveOutSpeed_;
};
