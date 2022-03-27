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
	float Speed_;			// �̵��ӵ�
	float Hp_;				// ü��
	float Recovery_;		// ü�� ���
	float Guard_;			// ����
	float Power_;			// ����
	float Range_;			// ���� ����(����, ����, ����, ���� �� ���� ���ݸ� �ش�)
	float ShootSpeed_;		// ����ü �ӵ�
	float ShootNum_;		// ����ü ��
	float Duration_;		// ��ų ���ӽð�


	// �нú�
	float Luck_;			// ������ Ȯ�� 3�� -> 4��
	float Growth_;			// ����ġ ȹ��� �߰� ����ġ
	float Greed_;			// �� ȹ��� �߰� ��
	float Magnet_;			// ������ ȹ�� ����

	int Revival_;			// ��Ȱ Ƚ��

};

