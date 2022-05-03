#pragma once
#include <GameEngine/GameEngineActor.h>
#include <map>
#include "GameInfo.h"


// ���� :
class GameEngineRenderer;
class GameEngineCollision;
class KingBible : public GameEngineActor
{
private:
	enum class STATE
	{
		SPIN,
		VANISH,
	};

public:
	// constrcuter destructer
	KingBible();
	~KingBible();

	// delete Function
	KingBible(const KingBible& _Other) = delete;
	KingBible(KingBible&& _Other) noexcept = delete;
	KingBible& operator=(const KingBible& _Other) = delete;
	KingBible& operator=(KingBible&& _Other) noexcept = delete;

protected:

	void Start() override;
	void Update() override;

private:
	STATE State_;
	void StateUpdate();
	void ChangeState(STATE _State);

	void SpinStart();
	void SpinUpdate();

	void VanishStart();
	void VanishUpdate();

private:

	GameEngineRenderer* BookRenderer_; // ���ͷ� ���� ��Ȳ�� �޶��� ����
	GameEngineCollision* BookCol_;

	// ��ų ����
	std::map<int, SkillStat> Bible_;
	int Level_;
	int BookCount_;
	float Range_; // �÷��̾�� å ������ �Ÿ�
};

