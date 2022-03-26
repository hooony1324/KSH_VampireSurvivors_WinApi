#pragma once
#include <GameEngine/GameEngineActor.h>

// ���� : 
class Character;
class Player : public GameEngineActor
{
public:
	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	void SetCharacter(Character _Type);
protected:

private:
	void Start() override;
	void Update() override;
	void Render() override;

	// �⺻ �ɷ�ġ (ü��, ���ǵ�, ���ݷ�, ...)
	float Speed_;



};

