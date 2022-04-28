#include <GameEngine/GameEngineActor.h>

enum class GemType
{
	GREEN,
	BLUE,
	RED
};


// ���� :
class GameEngineCollision;
class ExpGem : public GameEngineActor
{
public:
	enum class GemState
	{
		MOVE_BACK,
		MOVE_FORWARD,
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

protected:

	void Start() override;
	void Update() override;


private:
	void GetCheck();
	void MoveBeforeCheck();
	void PlayerCheck();

	static float RedExp_;

	GameEngineRenderer* Renderer_;
	GameEngineCollision* Col_;
	float Exp_;
	GemType Type_;

	// �÷��̾� ��ȣ�ۿ�
	float4 PlayerPos_;
	float4 Pos_;
	float4 MoveDir_;
	bool Get_;
};
