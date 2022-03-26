#pragma once

// Ό³Έν :
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

