#pragma once
#include "GameEngineBase/GameEngineNameObject.h"
#include <list>
#include <map>

// ���� :
class GameEngine;
class GameEngineActor;
class GameEngineLevel : public GameEngineNameObject
{
	friend GameEngine;
public:
	// constrcuter destructer
	GameEngineLevel();
	
	virtual ~GameEngineLevel();

	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

protected:
	
	// ���ҽ��� ���͸� �����ϴ� �ܰ�
	virtual void Loading() = 0;
	// �� ������ ���� ������ �� �ؾ��� ���� ����
	virtual void Update() = 0;
	// CurrentLevel => NextLevel �� ������ ������ �����ϴ� �Լ�
	virtual void SceneChangeStart() {}
	// CurrentLevle => NextLevel �� ���� ������ ������ �����ϴ� �Լ�
	virtual void SceneChangeEnd() {}

	template<typename ActorType>
	ActorType* CreateActor(const std::string& _Name, int _Order)
	{
		ActorType* NewActor = new ActorType();
		NewActor->SetName(_Name);
		NewActor->SetLevel(this);

		std::list<GameEngineActor*>& Group = AllActor_[_Order];
		Group.push_back(NewActor);

		return nullptr;
	}

private:
	// list���� : ������ �������� ��� Actor�� ��������/���� �� �Ͼ �� �ֱ� ����
	std::map<int, std::list<GameEngineActor*>> AllActor_;

	void ActorUpdate();
	void ActorRender();
};

