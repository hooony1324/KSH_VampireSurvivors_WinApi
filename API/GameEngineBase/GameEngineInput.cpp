#include "GameEngineInput.h"
#include "GameEngineDebug.h"
#include "GameEngineString.h"

void GameEngineInput::GameEngineKey::Update(float _DeltaTime)
{
	// � Ű�� �Է��� ������ ��
	if (true == KeyCheck())
	{
		// Free_ ���¿��� � Ű�� ���� ��Ȳ
		if (true == Free_)
		{
			Down_ = true;	// ��ư�� ����
			Press_ = true;	// ��ư ������ ����
			Up_ = false;
			Free_ = false;
			Time_ = 0.0f;
			Time_ += _DeltaTime;
		}
		// �̹� �Է��� �־��� ��Ȳ���� ���� ��Ȳ(������ �ִ�)
		else if (true == Press_)
		{
			Down_ = false;
			Press_ = true;
			Up_ = false;
			Free_ = false;
			Time_ += _DeltaTime;
		}
	}
	// Ű�� �Է��� ���� ��
	else
	{
		// Press_�� �� ��Ȳ
		if (true == Press_)
		{
			Down_ = false;
			Press_ = false;
			Up_ = true;
			Free_ = false;
			Time_ = 0.0f;
		}
		
		// Press�� ���� ��ư�� Up�� ��Ȳ -> Free����
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

// ����� ���� �ִ� Ű Ȯ��
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
		MsgBoxAssert("�̹� �����ϴ� �̸��� Ű�� �� ������� �߽��ϴ�.");
		return;
	}

	// �ҹ��� -> �빮��
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
		MsgBoxAssert("�������� �ʴ� Ű �Դϴ�");
		return false;
	}
	return AllInputKey_[UpperKey].Time_;
}

bool GameEngineInput::IsDown(const std::string& _Name)
{
	std::string UpperKey = GameEngineString::ToUpperReturn(_Name);

	if (AllInputKey_.end() == AllInputKey_.find(UpperKey))
	{
		MsgBoxAssert("�������� �ʴ� Ű �Դϴ�.");
		return false;
	}

	return AllInputKey_[UpperKey].Down_;
}
bool GameEngineInput::IsUp(const std::string& _Name)
{
	std::string UpperKey = GameEngineString::ToUpperReturn(_Name);

	if (AllInputKey_.end() == AllInputKey_.find(UpperKey))
	{
		MsgBoxAssert("�������� �ʴ� Ű �Դϴ�.");
		return false;
	}
	return AllInputKey_[UpperKey].Up_;
}
bool GameEngineInput::IsPress(const std::string& _Name)
{
	std::string UpperKey = GameEngineString::ToUpperReturn(_Name);

	if (AllInputKey_.end() == AllInputKey_.find(UpperKey))
	{
		MsgBoxAssert("�������� �ʴ� Ű �Դϴ�.");
		return false;
	}
	return AllInputKey_[UpperKey].Press_;
}
bool GameEngineInput::IsFree(const std::string& _Name)
{
	std::string UpperKey = GameEngineString::ToUpperReturn(_Name);

	if (AllInputKey_.end() == AllInputKey_.find(UpperKey))
	{
		MsgBoxAssert("�������� �ʴ� Ű �Դϴ�.");
		return false;
	}
	return AllInputKey_[UpperKey].Free_;
}