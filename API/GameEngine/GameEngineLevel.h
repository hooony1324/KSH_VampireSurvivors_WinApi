#pragma once
#include <list>
#include <map>
#include <GameEngineBase/GameEngineNameObject.h>
#include <GAmeEngineBase/GameEngineMath.h>

// 설명 :
class GameEngine;
class GameEngineActor;
class GameEngineCollision;
class GameEngineRenderer;
class GameEngineLevel : public GameEngineNameObject
{
	friend GameEngine;
	friend GameEngineActor;
	friend GameEngineCollision;
	friend GameEngineRenderer;
public:
	// constrcuter destructer
	GameEngineLevel();
	
	virtual ~GameEngineLevel();

	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

	template<typename ActorType>
	ActorType* CreateActor(int _Order = 0, const std::string& _Name = "")
	{
		ActorType* NewActor = new ActorType();
		GameEngineActor* StartActor = NewActor;
		NewActor->SetName(_Name);
		NewActor->SetLevel(this);
		StartActor->Start();
		std::list<GameEngineActor*>& Group = AllActor_[_Order];
		Group.push_back(NewActor);

		return NewActor;
	}

	inline float4 GetCameraPos()
	{
		return CameraPos_;
	}

	inline void MoveCameraPos(const float4& _Value)
	{
		CameraPos_ += _Value;
	}

	inline void SetCameraPos(const float4& _Value)
	{
		CameraPos_ = _Value;
	}

protected:
	
	// 래벨 생성 시, 리소스나 액터를 가져오는 단계
	virtual void Loading() = 0;
	// 이 레벨이 현재 레벨일 때 해야할 일을 실행
	virtual void Update() = 0;
	// CurrentLevel => NextLevel 시 현재의 레벨이 실행하는 함수
	virtual void LevelChangeStart() {}
	// CurrentLevle => NextLevel 시 현재 이전의 레벨이 실행하는 함수
	virtual void LevelChangeEnd() {}

private:
	// list이유 : 렌더링 순서, 복잡한 컨텐츠의 경우 Actor간 순서변경/삭제 가 일어날 수 있음
	std::map<int, std::list<GameEngineActor*>> AllActor_;

	void ActorUpdate();
	void ActorRender();
	void CollisionDebugRender();
	void ActorRelease();

	float4 CameraPos_;

private:
	std::map<int, std::list<GameEngineRenderer*>> AllRenderer_;

	void AddRenderer(GameEngineRenderer* _Renderer);

	void ChangeRenderOrder(GameEngineRenderer* _Renderer, int _NewOrder);

private:
	// 콜라이더는 엑터가 삭제, 콜라이더들은 Level이 관리
	std::map<std::string, std::list<GameEngineCollision*>> AllCollision_;

	void AddCollision(const std::string& _GroupName, GameEngineCollision* _Collision);
};

