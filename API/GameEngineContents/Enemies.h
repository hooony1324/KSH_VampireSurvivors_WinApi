#pragma once

// Ό³Έν :
class Enemies
{
public:
	// constrcuter destructer
	Enemies();
	virtual ~Enemies();

	// delete Function
	Enemies(const Enemies& _Other) = delete;
	Enemies(Enemies&& _Other) noexcept = delete;
	Enemies& operator=(const Enemies& _Other) = delete;
	Enemies& operator=(Enemies&& _Other) noexcept = delete;

protected:

private:

};

