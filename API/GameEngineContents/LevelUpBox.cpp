#include "LevelUpBox.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GameEnum.h"
#include "GameInfo.h"
#include "LevelUpUI.h"

LevelUpBox::LevelUpBox() 
	: Col_(nullptr)
{
}

LevelUpBox::~LevelUpBox() 
{
}

void LevelUpBox::Start()
{
	GameEngineRenderer* Renderer_ = CreateRenderer("BoxOpen.bmp");
	SetScale(Renderer_->GetScale());

	Col_ = CreateCollision("LevelUpBox", Renderer_->GetScale());

	NextLevelOff();
}

void LevelUpBox::Update()
{
	if (false == Col_->CollisionCheck("Player"))
	{
		return;
	}


	// �ϴ��� LevelUPUI, ���Ŀ� �������� ���ϸ��̼�����
	LevelUpUI::State_ = LevelUpUI::STATE::BOXES;
	LevelUpUI::CreateCount_ += 1;
	
	// LevelUpUI���¼���
	// 8���� ���� ������ �нú��� ���� Ȯ��
	// LevelUpUI���� -> ��������
	

	Death();

}

void LevelUpBox::Render()
{
}