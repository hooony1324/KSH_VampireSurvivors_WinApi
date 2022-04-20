#pragma once
#include <string>
#include <GameEngineBase/GameEngineMath.h>

enum class CharacterType
{
	Old = 0,
	Cavallo,
	Imelda,
	MAX
};

// ���� : 
class Character
{
public:

public:
	// constrcuter destructer
	Character();
	Character(CharacterType _CharacterType);
	~Character();

	// delete Function
	Character(const Character& _Other) = delete;
	Character(Character&& _Other) noexcept = delete;
	Character& operator=(const Character& _Other) = delete;
	Character& operator=(Character&& _Other) noexcept = delete;

	void SetCharacter(CharacterType _CharacterType);


	//ĳ���� ������ ����
public:
	std::string ImageName_;
	std::string Name_;
	std::string WalkRightAnim_;
	std::string WalkLeftAnim_;

	// �нú� �⺻ �ɷ�ġ (ü��, ���ǵ�, ���ݷ�, ...)
	float Speed_;			// �̵��ӵ�
	float MaxHp_;			
	float CurrentHp_;		// ü�� ���ִ� ä�� �����ϴ� ĳ���� ���� 
	float Recovery_;		// ü�� ���
	float Guard_;			// ����
	float Power_;			// �߰� ������, ����
	float MeleeRange_;		// ���� ���� ����(����, ����, ����, ���� �� ���� ���ݸ� �ش�)
	float ShootSpeedRatio_;	// ��ü ����ü �ӵ� ��������
	float AddShootNum_;		// �߰� ����ü ��
	float Duration_;		// ��ų ���ӽð�


	// �нú� ���� �ɷ�ġ
	float Luck_;			// ������ Ȯ�� 3�� -> 4��
	float Growth_;			// ����ġ ȹ��� �߰� ����ġ
	float Greed_;			// �� ȹ��� �߰� ��
	float Magnet_;			// ������ ȹ�� ����
	int Revival_;			// ��Ȱ Ƚ��


};

