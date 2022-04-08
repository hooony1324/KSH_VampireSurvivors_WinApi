#pragma once
#include "GameEngineNameObject.h"
#include "ThirdParty/inc/fmod.hpp"
#include <map>

class GameEngineSoundPlayer;
// ���� :
class GameEngineSound : public GameEngineNameObject
{
public:
	// constrcuter destructer
	GameEngineSound();
	~GameEngineSound();

	// delete Function
	GameEngineSound(const GameEngineSound& _Other) = delete;
	GameEngineSound(GameEngineSound&& _Other) noexcept = delete;
	GameEngineSound& operator=(const GameEngineSound& _Other) = delete;
	GameEngineSound& operator=(GameEngineSound&& _Other) noexcept = delete;

protected:
	bool Load(const std::string& _Path);


private:
	FMOD::Sound* Sound;

	///////////////////////////////////////// �Ŵ�����Ʈ ���� ���
public:
	// �׳� ���� ���1ȸ ����� ���߰ų� �̷��� ���մϴ�.
	static GameEngineSoundPlayer SoundPlayControl(const std::string& _Name);

	static void SoundPlayOneShot(const std::string& _Name);
	static void Update();

	/// <summary>
	/// ///////////////////////////////////// ���ҽ� �Ŵ�����Ʈ
	/// </summary>
public:
	static GameEngineSound* FindRes(const std::string& _Name);
	static GameEngineSound* LoadRes(const std::string& _Path);
	static GameEngineSound* LoadRes(const std::string& _Path, const std::string& _Name);

	static void AllResourcesDestroy();

private:
	static std::map<std::string, GameEngineSound*> AllRes;

};

// ���� ����� �����Ҽ� �ִ� ��ɵ��� �����̴ϴ�.
class GameEngineSound;
class GameEngineSoundPlayer
{
	friend GameEngineSound;

public:
	void Stop();

	GameEngineSoundPlayer(const GameEngineSoundPlayer& _Other);

private:
	GameEngineSound* Sound_;
	FMOD::Channel* ControlHandle_;


	GameEngineSoundPlayer(GameEngineSound* Sound, FMOD::Channel* ControlHandle);

public:
	GameEngineSoundPlayer();
	~GameEngineSoundPlayer();
};