#pragma once

// ���� : GameName - Ŭ������
class Suora
{
public:
	// constrcuter destructer
	Suora();
	~Suora();

	// delete Function
	Suora(const Suora& _Other) = delete;
	Suora(Suora&& _Other) noexcept = delete;
	Suora& operator=(const Suora& _Other) = delete;
	Suora& operator=(Suora&& _Other) noexcept = delete;

protected:

private:

};

