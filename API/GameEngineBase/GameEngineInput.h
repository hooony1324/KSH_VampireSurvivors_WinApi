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

		float Time_;
		int Key_;			

		bool KeyCheck()
		{
			return 0 != GetAsyncKeyState(Key_);
		}

		void Update(float _DeltaTime);

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
	void Update(float _DeltaTime = 0.0f);
	void CreateKey(const std::string _Name, int _Key);

	float GetTime(const std::string& _Name);
	bool IsDown(const std::string& _Name);
	bool IsUp(const std::string& _Name);
	bool IsPress(const std::string& _Name);
	bool IsFree(const std::string& _Name);
	bool IsKey(const std::string& _Name);

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

