#pragma once

// Ό³Έν :
class Counter
{
public:
	Counter(float _CountingTime);

	inline bool Start(float _DeltaTime)
	{
		if (0 < CountingTime_)
		{
			CountingTime_ -= _DeltaTime;
			return false;
		}

		return true;
	}

protected:

private:
	float CountingTime_;

	// constrcuter destructer
	Counter();

	~Counter();

	// delete Function
	Counter(const Counter& _Other) = delete;
	Counter(Counter&& _Other) noexcept = delete;
	Counter& operator=(const Counter& _Other) = delete;
	Counter& operator=(Counter&& _Other) noexcept = delete;
};

