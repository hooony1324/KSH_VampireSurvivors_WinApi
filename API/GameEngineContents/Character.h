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


	// ���� ����Ʈ(���� ����) WeaponList* wpList;

};

