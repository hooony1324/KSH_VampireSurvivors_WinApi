#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include "Character.h"

// 설명 :
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

	// 계속 업데이트 되야 되는 정보
	static float4 PlayerPos_;

	// Player클래스가 최후에 넘겨줘야되는 정보
	float MaxExp_;
	float CurrentExp_;
	int PlayerLevel_;
	int SurvivalTime_;
	int EearnedGold_;
	int KillCount_;

	// + 무기정보, ...
	



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

