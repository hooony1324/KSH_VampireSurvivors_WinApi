#pragma once

// 설명 :
// Title레벨 에서 캐릭터를 설정하고 Play레벨에 Character정보 넘겨준다
// 캐릭터 정보
// 이름 : 포, 클레리씨, etc..
// 능력치 : 체력, 공격력 등
// 
// 
class Character
{
public:
	// constrcuter destructer
	Character();
	~Character();

	// delete Function
	Character(const Character& _Other) = delete;
	Character(Character&& _Other) noexcept = delete;
	Character& operator=(const Character& _Other) = delete;
	Character& operator=(Character&& _Other) noexcept = delete;

protected:

private:

public:
	int Hp_;
	int Speed_;
	int Damage_;

};

