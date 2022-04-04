#pragma once
#include <list>
#include <map>
#include <GameEngineBase/GameEngineNameObject.h>
#include <GAmeEngineBase/GameEngineMath.h>

// ���� :
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
	
	// ���� ���� ��, ���ҽ��� ���͸� �������� �ܰ�
	virtual void Loading() = 0;
	// �� ������ ���� ������ �� �ؾ��� ���� ����
	virtual void Update() = 0;
	// CurrentLevel => NextLevel �� ������ ������ �����ϴ� �Լ�
	virtual void LevelChangeStart() {}
	// CurrentLevle => NextLevel �� ���� ������ ������ �����ϴ� �Լ�
	virtual void LevelChangeEnd() {}

private:
	// list���� : ������ ����, ������ �������� ��� Actor�� ��������/���� �� �Ͼ �� ����
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
	// �ݶ��̴��� ���Ͱ� ����, �ݶ��̴����� Level�� ����
	std::map<std::string, std::list<GameEngineCollision*>> AllCollision_;

	void AddCollision(const std::string& _GroupName, GameEngineCollision* _Collision);
};

