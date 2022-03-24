#pragma once
#include <Windows.h>
#include <map>
#include <string>

// 설명 :
class GameEngineInput
{
private:
	class GameEngineKey
	{
		friend GameEngineInput;

		bool Down_;			// 최초로 누를 때
		bool Press_;		// 이미 누른 상태를 유지할 때
		bool Up_;			// 이미 누른 상태에서 땔 때
		bool Free_;			// 땐 상태

		int Key_;			

		bool KeyCheck()
		{
			return 0 != GetAsyncKeyState(Key_);
		}

		void Update();

		void Reset()
		{
			Down_ = false;
			Press_ = false;
			Up_ = false;
			Free_ = true;
		}

	};

private:
	static GameEngineInput* Inst_;

public:
	static GameEngineInput* GetInst()
	{
		return Inst_;
	}

	static void Destroy()
	{
		if (nullptr != Inst_)
		{
			delete Inst_;
			Inst_ = nullptr;
		}
	}

public:
	void Update();
	void CreateKey(std::string _Name, int _Key);

	bool IsDown(std::string _Name);
	bool IsUp(std::string _Name);
	bool IsPress(std::string _Name);
	bool IsFree(std::string _Name);
	bool IsKey(std::string _Name);

protected:

private:
	std::map<std::string, GameEngineKey> AllInputKey_;

	// constrcuter destructer
	GameEngineInput();
	~GameEngineInput();

	// delete Function
	GameEngineInput(const GameEngineInput& _Other) = delete;
	GameEngineInput(GameEngineInput&& _Other) noexcept = delete;
	GameEngineInput& operator=(const GameEngineInput& _Other) = delete;
	GameEngineInput& operator=(GameEngineInput&& _Other) noexcept = delete;
};

