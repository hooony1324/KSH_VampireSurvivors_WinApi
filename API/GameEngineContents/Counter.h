#pragma once

// Ό³Έν :
class Counter
{
public:
	// constrcuter destructer
	Counter();
	Counter(float _CountingTime);
	~Counter();

	// delete Function
	Counter(const Counter& _Other) = delete;
	Counter(Counter&& _Other) noexcept = delete;
	Counter& operator=(const Counter& _Other) = delete;
	Counter& operator=(Counter&& _Other) noexcept = delete;

	inline bool Start(float _DeltaTime)
	{
		if (0 < CountingTime_)
		{
			CountingTime_ -= _DeltaTime;
			return false;
		}

		return true;
	}

	inline void SetCount(float _CountingTime)
	{
		CountingTime_ = _CountingTime;
	}

protected:

private:
	float CountingTime_;

};

