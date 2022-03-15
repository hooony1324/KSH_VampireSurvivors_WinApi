#pragma once
#include "GameEngineBase/GameEngineNameObject.h"
#include <list>
#include <map>

// 설명 :
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
	
	// 리소스나 액터를 생성하는 단계
	virtual void Loading() = 0;
	// 이 레벨이 현재 레벨일 때 해야할 일을 실행
	virtual void Update() = 0;
	// CurrentLevel => NextLevel 시 현재의 레벨이 실행하는 함수
	virtual void SceneChangeStart() {}
	// CurrentLevle => NextLevel 시 현재 이전의 레벨이 실행하는 함수
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
	// list이유 : 복잡한 컨텐츠의 경우 Actor간 순서변경/삭제 가 일어날 수 있기 때문
	std::map<int, std::list<GameEngineActor*>> AllActor_;

	void ActorUpdate();
	void ActorRender();
};

