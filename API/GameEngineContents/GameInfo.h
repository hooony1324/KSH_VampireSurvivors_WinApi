#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include "Character.h"

// ���� :
class GameInfo
{
public:

	static void SetCharacter(CharacterType _CharacterType)
	{
		if (nullptr != Character_)
		{
			delete Character_;
		}
		Character_ = new Character(_CharacterType);
	}

	static Character* GetCharacter()
	{
		return Character_;
	}

	static void SetPlayerPos(float4 _PlayerPos)
	{
		PlayerPos_ = _PlayerPos;
	}

	static float4 GetPlayerPos()
	{
		return PlayerPos_;
	}


	static void Destroy()
	{
		if (nullptr != Character_)
		{
			delete Character_;
			Character_ = nullptr;
		}
	}

private:
	static Character* Character_;

	// ��� ������Ʈ �Ǿ� �Ǵ� ����
	static float4 PlayerPos_;

	// PlayerŬ������ ���Ŀ� �Ѱ���ߵǴ� ����
	float MaxExp_;
	float CurrentExp_;
	int PlayerLevel_;
	int SurvivalTime_;
	int EearnedGold_;
	int KillCount_;

	// + ��������, ...
	



protected:

private:
	// constrcuter destructer
	GameInfo();
	~GameInfo();

	// delete Function
	GameInfo(const GameInfo& _Other) = delete;
	GameInfo(GameInfo&& _Other) noexcept = delete;
	GameInfo& operator=(const GameInfo& _Other) = delete;
	GameInfo& operator=(GameInfo&& _Other) noexcept = delete;

};

