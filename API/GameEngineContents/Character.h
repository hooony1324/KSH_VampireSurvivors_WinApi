#pragma once
#include <string>

// ���� :
class Character
{
public:
	enum class Type
	{
		Old = 0,
		Cavallo,
		Imelda,
	};

public:
	// constrcuter destructer
	Character();		// ����Ʈ ĳ���ʹ� "old.bmp" �Դϴ�
	~Character();

	// delete Function
	Character(const Character& _Other) = delete;
	Character(Character&& _Other) noexcept = delete;
	Character& operator=(const Character& _Other) = delete;
	Character& operator=(Character&& _Other) noexcept = delete;

	void SetDefault();
	void SetOld();
	void SetCavallo();
	void SetImelda();

protected:

public:
	// ĳ���� �̹��� �̸� ex)old.bmp
	std::string ImageName_;
	std::string Name_;

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

