#pragma once

// Ό³Έν : GameName - Ζχ
class Old
{
public:
	// constrcuter destructer
	Old();
	~Old();

	// delete Function
	Old(const Old& _Other) = delete;
	Old(Old&& _Other) noexcept = delete;
	Old& operator=(const Old& _Other) = delete;
	Old& operator=(Old&& _Other) noexcept = delete;

protected:

private:

};

