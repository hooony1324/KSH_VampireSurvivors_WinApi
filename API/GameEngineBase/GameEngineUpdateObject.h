#pragma once
#include <string>
#include "GameEngineTime.h"

// ���� :
// ������ �׻� ������Ʈ�� �Ǿ����
// �ݸ鿡 �÷��̾�, ���ʹ� ȭ�鿡 ��� �Ⱥ��̰� �Ѵٰų�
// �ƿ� �׾��ٴ� ó���� �� �� �־�� �Ѵ�
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

	// DeathTime�����Ǹ� ReleaseUpdate�� Actor Update�ֱ⿡ �߰�
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

