#include <GameEngine/GameEngineActor.h>

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
	void PlayerCheck();

	static float RedExp_;

	GameEngineRenderer* Renderer_;
	GameEngineCollision* Col_;
	float Exp_;
	GemType Type_;

	// 플레이어 상호작용
	
};
