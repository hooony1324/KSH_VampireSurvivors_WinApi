#include "GameEngineSound.h"
#include "GameEnginePath.h"
#include "GameEngineDebug.h"
#include "GameEngineString.h"


#pragma comment(lib, "fmod_vc.lib")

FMOD::System* SoundSystem_ = nullptr;

class SoundSystemCreater
{
public:
	SoundSystemCreater()
	{
		FMOD::System_Create(&SoundSystem_);

		if (nullptr == SoundSystem_)
		{
			MsgBoxAssert("���� �ý��� ������ �����߽��ϴ�.");
			return;
		}

		// �츮 ��ǻ�� ���� ī�忡 ���� ������ ������
		if (FMOD_OK != SoundSystem_->init(32, FMOD_DEFAULT, nullptr))
		{
			MsgBoxAssert("���� �ý��� ������ �����߽��ϴ�.");
			return;
		}

	}
};

SoundSystemCreater CreateInst = SoundSystemCreater();

GameEngineSound::GameEngineSound()
{
	// FMOD::System_Create();
}

GameEngineSound::~GameEngineSound()
{
}

bool GameEngineSound::Load(const std::string& _Path)
{
	if (FMOD_OK != SoundSystem_->createSound(_Path.c_str(), FMOD_LOOP_NORMAL, nullptr, &Sound))
	{
		MsgBoxAssertString("���� �ε忡 �����߽��ϴ�.\n ��� : " + _Path);
		return false;
	}

	return true;
}

/// /////////////////////////////////////////////////////////////// ��� �Ŵ�����Ʈ

GameEngineSoundPlayer GameEngineSound::SoundPlayControl(const std::string& _Name)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Name);

	GameEngineSound* FindSound = FindRes(UpperName);

	if (nullptr == FindSound)
	{
		MsgBoxAssertString("�������� �ʴ� ���带 ����Ϸ��� �߽��ϴ�.\n �̸� : " + UpperName);
		return GameEngineSoundPlayer();
	}

	FMOD::Channel* PlayControl = nullptr;

	SoundSystem_->playSound(FindSound->Sound, nullptr, false, &PlayControl);

	return GameEngineSoundPlayer(FindSound, PlayControl);
}

void GameEngineSound::SoundPlayOneShot(const std::string& _Name, int LoopCount /*= 1*/)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Name);

	GameEngineSound* FindSound = FindRes(UpperName);

	if (nullptr == FindSound)
	{
		MsgBoxAssertString("�������� �ʴ� ���带 ����Ϸ��� �߽��ϴ�.\n �̸� : " + UpperName);
		return;
	}

	FMOD::Channel* PlayControl = nullptr;

	SoundSystem_->playSound(FindSound->Sound, nullptr, false, &PlayControl);

	PlayControl->setLoopCount(LoopCount);



}

void GameEngineSound::Update()
{
	if (nullptr == SoundSystem_)
	{
		return;
	}
	SoundSystem_->update();
}

/// /////////////////////////////////////////////////////////////// �Ŵ�����Ʈ

std::map<std::string, GameEngineSound*> GameEngineSound::AllRes;


GameEngineSound* GameEngineSound::FindRes(const std::string& _Name)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Name);

	std::map<std::string, GameEngineSound*>::iterator FindIter = AllRes.find(UpperName);

	if (FindIter == AllRes.end())
	{
		return nullptr;
	}

	return FindIter->second;
}
GameEngineSound* GameEngineSound::LoadRes(const std::string& _Path)
{
	GameEnginePath NewPath = GameEnginePath(_Path);
	return LoadRes(_Path, NewPath.GetFileName());	//��ο� �����̸�(ex.idle.bmp)�� Map�� key,value�� �ֱ����� ���� �Ѱ��ش�.
}
GameEngineSound* GameEngineSound::LoadRes(const std::string& _Path, const std::string& _Name)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Name);

	GameEngineSound* NewRes = new GameEngineSound();

	if (false == NewRes->Load(_Path))
	{
		delete NewRes;
		NewRes = nullptr;
		return nullptr;
	}

	AllRes.insert(std::make_pair(UpperName, NewRes));
	return nullptr;
}

void GameEngineSound::AllResourcesDestroy()
{
	for (std::pair<std::string, GameEngineSound*> Res : AllRes)
	{
		delete Res.second;
		Res.second = nullptr;
	}

	AllRes.clear();

	if (nullptr != SoundSystem_)
	{
		SoundSystem_->release();
		SoundSystem_ = nullptr;
	}
}

////////////////////////////////////////////////////////// ���� �÷��̾�

void GameEngineSoundPlayer::Stop()
{
	if (nullptr == ControlHandle_)
	{
		MsgBoxAssert("���� ��Ʈ�� ä�ο� ġ������ ������ �ֽ��ϴ�.\n");
		return;
	}

	ControlHandle_->stop();
}


GameEngineSoundPlayer::GameEngineSoundPlayer()
	: Sound_(nullptr)
	, ControlHandle_(nullptr)
{

}

GameEngineSoundPlayer::GameEngineSoundPlayer(const GameEngineSoundPlayer& _Other)
	: Sound_(_Other.Sound_)
	, ControlHandle_(_Other.ControlHandle_)
{

}

GameEngineSoundPlayer::GameEngineSoundPlayer(GameEngineSound* _Sound, FMOD::Channel* _ControlHandle)
	: Sound_(_Sound)
	, ControlHandle_(_ControlHandle)
{

}

GameEngineSoundPlayer::~GameEngineSoundPlayer()
{

}