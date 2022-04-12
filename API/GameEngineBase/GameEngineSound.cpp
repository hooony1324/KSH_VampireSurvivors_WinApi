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
			MsgBoxAssert("사운드 시스템 생성에 실패했습니다.");
			return;
		}

		// 우리 컴퓨터 사운드 카드에 대한 정보를 얻어오고
		if (FMOD_OK != SoundSystem_->init(32, FMOD_DEFAULT, nullptr))
		{
			MsgBoxAssert("사운드 시스템 설정이 실패했습니다.");
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
		MsgBoxAssertString("사운드 로드에 실패했습니다.\n 경로 : " + _Path);
		return false;
	}

	return true;
}

/// /////////////////////////////////////////////////////////////// 기능 매니지먼트

GameEngineSoundPlayer GameEngineSound::SoundPlayControl(const std::string& _Name)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Name);

	GameEngineSound* FindSound = FindRes(UpperName);

	if (nullptr == FindSound)
	{
		MsgBoxAssertString("존재하지 않는 사운드를 재생하려고 했습니다.\n 이름 : " + UpperName);
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
		MsgBoxAssertString("존재하지 않는 사운드를 재생하려고 했습니다.\n 이름 : " + UpperName);
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

/// /////////////////////////////////////////////////////////////// 매니지먼트

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
	return LoadRes(_Path, NewPath.GetFileName());	//경로와 파일이름(ex.idle.bmp)을 Map의 key,value로 넣기위해 각각 넘겨준다.
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

////////////////////////////////////////////////////////// 사운드 플레이어

void GameEngineSoundPlayer::Stop()
{
	if (nullptr == ControlHandle_)
	{
		MsgBoxAssert("사운드 컨트롤 채널에 치명적인 문제가 있습니다.\n");
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