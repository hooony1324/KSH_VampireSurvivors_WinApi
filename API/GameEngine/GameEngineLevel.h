#pragma once
#include <list>
#include <map>
#include <set>
#include <vector>
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineMath.h>

class GameEngineActor;
struct ChangeOrderItem
{
	GameEngineActor* TargetObject; // �̳༮��
	int ChangeOrder; // �̷��� �ٲ��.
};

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

	// �Ҹ��� virtual �߿�
	virtual ~GameEngineLevel();

	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

	static void IsDebugModeOn()
	{
		IsDebug = true;
	}

	static void IsDebugModeOff()
	{
		IsDebug = false;
	}

	static void IsDebugModeSwitch()
	{
		IsDebug = !IsDebug;
	}

	template<typename ActorType>
	ActorType* CreateActor(int _Order = 0, const std::string& _Name = "")
	{
		ActorType* NewActor = new ActorType();
		GameEngineActor* StartActor = NewActor;
		NewActor->GameEngineUpdateObject::SetOrder(_Order);
		NewActor->SetName(_Name);
		NewActor->SetLevel(this);
		StartActor->Start();
		std::list<GameEngineActor*>& Group = AllActor_[_Order];
		Group.push_back(NewActor);

		//// _Order ���͵��� ���ư��� ������ �ǹ��ϰ� �ȴ�.
		//// insert�� find�� ���ÿ�
		//std::map<int, std::list<GameEngineActor*>>::iterator FindGroup
		//	= AllActor_.find(_Order);

		//if (FindGroup == AllActor_.end())
		//{

		//	// AllActor_.insert(std::make_pair(_Order, std::list<GameEngineActor*>()));
		//	// �̰Դ� ����
		//	AllActor_.insert(
		//		std::map<int, std::list<GameEngineActor*>>::value_type(_Order, std::list<GameEngineActor*>())
		//	);
		//	FindGroup = AllActor_.find(_Order);
		//}

		return NewActor;
	}

	inline float4 GetCameraPos()
	{
		return CameraPos_;
	}

	inline void ResetOn()
	{
		IsReset = true;
	}

	inline void MoveCameraPos(const float4& _Value)
	{
		CameraPos_ += _Value;
	}

	inline void SetCameraPos(const float4& _Value)
	{
		CameraPos_ = _Value;
	}

	template<typename ConvertType>
	ConvertType* FindActor(const std::string& _Name)
	{
		return dynamic_cast<ConvertType*>(FindActor(_Name));
	}

	GameEngineActor* FindActor(const std::string& _Name);

	void RegistActor(const std::string& _Name, GameEngineActor* _Actor);

	// �� ������ sort�� �ϰڴ�.
	void YSortOn(int _SortOrder)
	{
		IsYSort_.insert(_SortOrder);
	}

protected:
	// �����Լ�
	// ��������鼭 ���ҽ��� ���͸� ���鶧 ���
	virtual void Loading() = 0;
	// �� ������ ���� �����϶� �ؾ������� �����Ѵ�.
	virtual void Update() = 0;
	// Current���� => Next������ �����Ҷ� ���緹���� �����ϴ� �Լ�.
	void ActorLevelChangeStart(GameEngineLevel* _PrevLevel);
	virtual void LevelChangeStart(GameEngineLevel* _PrevLevel) {}
	// Current���� => Next������ �����Ҷ� ���������� �����ϴ� �Լ�.
	void ActorLevelChangeEnd(GameEngineLevel* _NextLevel);
	virtual void LevelChangeEnd(GameEngineLevel* _NextLevel) {}

	void ObjectLevelMoveCheck(GameEngineLevel* _NextLevel);

	void Reset();

	virtual void UserResetEnd() {}

private:
	static bool IsDebug;

	bool IsReset;

	// std::vector�� �����ϴ°� �� ���ٰ� ����..
	std::map<int, std::list<GameEngineActor*>> AllActor_;

	std::map<std::string, GameEngineActor*> RegistActor_;

	std::vector<ChangeOrderItem> ChangeOrderList;

	float4 CameraPos_;

	void ActorUpdate();
	void ActorRender();
	void CollisionDebugRender();
	void ActorRelease();

private:
	std::map<int, std::list<GameEngineRenderer*>> AllRenderer_;

	// �����ϳ� ���ϳ�
	std::set<int> IsYSort_;

	void AddRenderer(GameEngineRenderer* _Renderer);

	void ChangeUpdateOrder(GameEngineActor* _Actor, int _Oreder);

	void ChangeRenderOrder(GameEngineRenderer* _Renderer, int _NewOrder);


private:
	// ������ ���Ͱ� ������ ���� ����� Level
	// ���⼭ �Ժη� GameEngineCollision*�� delete �ϴ� ���� ������ �ȵȴ�.,
	std::map<std::string, std::list<GameEngineCollision*>> AllCollision_;

	void AddCollision(const std::string& _GroupName, GameEngineCollision* _Collision);
};
