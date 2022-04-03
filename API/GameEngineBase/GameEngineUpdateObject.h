#pragma once
#include <string>
#include "GameEngineTime.h"

// 설명 :
// 레벨은 항상 업데이트가 되어야함
// 반면에 플레이어, 몬스터는 화면에 잠깐 안보이게 한다거나
// 아예 죽었다는 처리를 할 수 있어야 한다
class GameEngineUpdateObject
{
public:
	// constrcuter destructer
	GameEngineUpdateObject();
	~GameEngineUpdateObject();

	// delete Function
	GameEngineUpdateObject(const GameEngineUpdateObject& _Other) = delete;
	GameEngineUpdateObject(GameEngineUpdateObject&& _Other) noexcept = delete;
	GameEngineUpdateObject& operator=(const GameEngineUpdateObject& _Other) = delete;
	GameEngineUpdateObject& operator=(GameEngineUpdateObject&& _Other) noexcept = delete;

	inline void On()
	{
		IsUpdate_ = true;
	}

	inline void Off()
	{
		IsUpdate_ = false;
	}

	inline virtual bool IsUpdate()
	{
		return IsUpdate_ && false == IsDeath_;
	}

	inline virtual bool IsDeath()
	{
		return IsDeath_;
	}

	inline void Death()
	{
		IsDeath_ = true;
	}

	// DeathTime설정되면 ReleaseUpdate를 Actor Update주기에 추가
	void ReleaseUpdate()
	{
		if (false == IsReleaseUpdate_)
		{
			return;
		}

		DeathTime_ -= GameEngineTime::GetDeltaTime();

		if (0.0f >= DeathTime_)
		{
			IsDeath_ = true;
		}
	}

	inline void Death(float _Time)
	{
		IsReleaseUpdate_ = true;
		DeathTime_ = _Time;
	}




private:
	bool IsReleaseUpdate_;
	float DeathTime_;

	bool IsUpdate_;
	bool IsDeath_;
};

