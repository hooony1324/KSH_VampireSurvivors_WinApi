#include "GameEngineInput.h"
#include "GameEngineDebug.h"
#include "GameEngineString.h"

void GameEngineInput::GameEngineKey::Update(float _DeltaTime)
{
	// 어떤 키의 입력이 존재할 때
	if (true == KeyCheck())
	{
		// Free_ 상태에서 어떤 키를 누른 상황
		if (true == Free_)
		{
			Down_ = true;	// 버튼이 눌림
			Press_ = true;	// 버튼 눌린걸 유지
			Up_ = false;
			Free_ = false;
			Time_ = 0.0f;
			Time_ += _DeltaTime;
		}
		// 이미 입력이 있었던 상황에서 누른 상황(누르고 있는)
		else if (true == Press_)
		{
			Down_ = false;
			Press_ = true;
			Up_ = false;
			Free_ = false;
			Time_ += _DeltaTime;
		}
	}
	// 키의 입력이 없을 때
	else
	{
		// Press_중 땐 상황
		if (true == Press_)
		{
			Down_ = false;
			Press_ = false;
			Up_ = true;
			Free_ = false;
			Time_ = 0.0f;
		}
		
		// Press중 때서 버튼이 Up된 상황 -> Free상태
		else if (true == Up_)
		{
			Down_ = false;
			Press_ = false;
			Up_ = false;
			Free_ = true;
		}
	}
}


GameEngineInput* GameEngineInput::Inst_ = new GameEngineInput();

GameEngineInput::GameEngineInput()
{
}

GameEngineInput::~GameEngineInput()
{
}

// 등록한 적이 있는 키 확인
bool GameEngineInput::IsKey(const std::string& _Name)
{
	std::string UpperKey = GameEngineString::ToUpperReturn(_Name);

	if (AllInputKey_.end() != AllInputKey_.find(UpperKey))
	{
		return true;
	}

	return false;
}

void GameEngineInput::CreateKey(std::string _Name, int _Key)
{
	std::string UpperKey = GameEngineString::ToUpperReturn(_Name);

	if (AllInputKey_.end() != AllInputKey_.find(UpperKey))
	{
		MsgBoxAssert("이미 존재하는 이름의 키를 또 만들려고 했습니다.");
		return;
	}

	// 소문자 -> 대문자
	if ('a' <= _Key && 'z' >= _Key)
	{
		_Key = std::toupper(_Key);
	}

	AllInputKey_.insert(std::make_pair(UpperKey, GameEngineKey()));
	AllInputKey_[UpperKey].Key_ = _Key;
	AllInputKey_[UpperKey].Reset();
}

void GameEngineInput::Update(float _DeltaTime)
{
	std::map<std::string, GameEngineKey>::iterator KeyUpdateStart = AllInputKey_.begin();
	std::map<std::string, GameEngineKey>::iterator KeyUpdateEnd = AllInputKey_.end();

	for (; KeyUpdateStart != KeyUpdateEnd; ++KeyUpdateStart)
	{
		GameEngineKey& CurrentKey = KeyUpdateStart->second;

		CurrentKey.Update(_DeltaTime);
	}

}

float GameEngineInput::GetTime(const std::string& _Name)
{
	std::string UpperKey = GameEngineString::ToUpperReturn(_Name);

	if (AllInputKey_.end() == AllInputKey_.find(UpperKey))
	{
		MsgBoxAssert("존재하지 않는 키 입니다");
		return false;
	}
	return AllInputKey_[UpperKey].Time_;
}

bool GameEngineInput::IsDown(const std::string& _Name)
{
	std::string UpperKey = GameEngineString::ToUpperReturn(_Name);

	if (AllInputKey_.end() == AllInputKey_.find(UpperKey))
	{
		MsgBoxAssert("존재하지 않는 키 입니다.");
		return false;
	}

	return AllInputKey_[UpperKey].Down_;
}
bool GameEngineInput::IsUp(const std::string& _Name)
{
	std::string UpperKey = GameEngineString::ToUpperReturn(_Name);

	if (AllInputKey_.end() == AllInputKey_.find(UpperKey))
	{
		MsgBoxAssert("존재하지 않는 키 입니다.");
		return false;
	}
	return AllInputKey_[UpperKey].Up_;
}
bool GameEngineInput::IsPress(const std::string& _Name)
{
	std::string UpperKey = GameEngineString::ToUpperReturn(_Name);

	if (AllInputKey_.end() == AllInputKey_.find(UpperKey))
	{
		MsgBoxAssert("존재하지 않는 키 입니다.");
		return false;
	}
	return AllInputKey_[UpperKey].Press_;
}
bool GameEngineInput::IsFree(const std::string& _Name)
{
	std::string UpperKey = GameEngineString::ToUpperReturn(_Name);

	if (AllInputKey_.end() == AllInputKey_.find(UpperKey))
	{
		MsgBoxAssert("존재하지 않는 키 입니다.");
		return false;
	}
	return AllInputKey_[UpperKey].Free_;
}