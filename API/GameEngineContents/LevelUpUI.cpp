#include "LevelUpUI.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngineBase/GameEngineRandom.h>

#include "ObjectEnum.h"
#include "GameInfo.h"

int LevelUpUI::CreateCount_ = 0;
bool LevelUpUI::IsActivated_ = false;

LevelUpUI::LevelUpUI() 
{
}

LevelUpUI::~LevelUpUI() 
{
}

void LevelUpUI::Start()
{
	// ��� 
	GameEngineRenderer* Renderer = CreateRenderer("LevelUpUI.bmp");
	SetScale(Renderer->GetScale());
	Renderer->CameraEffectOff();
	Renderer->SetPivot(GameEngineWindow::GetScale().Half() + float4{0, 10});

	// ����
	GameEngineSound::SoundPlayOneShot("LevelUp.MP3", 0);
	GameInfo::SetPause(true);
	IsActivated_ = true;

	int SelectNum = 3;
	// ���� ���� �ڽ� 1
	Renderer1_ = CreateRenderer();
	Renderer1_->SetImage("LevelUpMagicwand.bmp");
	Renderer1_->CameraEffectOff();
	Renderer1_->SetPivot(GameEngineWindow::GetScale().Half() + float4{2, -Renderer1_->GetImageScale().y});

	// ���� ���� �ڽ� 2
	Renderer2_ = CreateRenderer();
	Renderer2_->SetImage("LevelUpMagicwand.bmp");
	Renderer2_->CameraEffectOff();
	Renderer2_->SetPivot(GameEngineWindow::GetScale().Half() + float4{ 2, 0 });

	// ���� ���� �ڽ� 3
	Renderer3_ = CreateRenderer();
	Renderer3_->SetImage("LevelUpMagicwand.bmp");
	Renderer3_->CameraEffectOff();
	Renderer3_->SetPivot(GameEngineWindow::GetScale().Half() + float4{ 2, Renderer1_->GetImageScale().y });

	// ���� ���� �ڽ� 4 ����� ����
	float PlayerLuck = GameInfo::GetPlayerInfo()->Luck_;
	//PlayerLuck = 30;
	GameEngineRandom Random;
	int Success = Random.RandomInt(1, 101);
	
	// ����
	if (Success <= PlayerLuck)
	{
		// ���� ���� �ڽ� 4
		Renderer4_ = CreateRenderer();
		Renderer4_->SetImage("LevelUpMagicwand.bmp");
		Renderer4_->CameraEffectOff();
		Renderer4_->SetPivot(GameEngineWindow::GetScale().Half() + float4{ 2, Renderer1_->GetImageScale().y * 2 });

		SelectNum = 4;
	}

	// �߿� : ó���� 0 ~ 10 ������ ���߿��� ���� ��ų�� ���¿� ���� ���� �� �ִ� ��ų�迭�� �޶����� �� ex. SelectableSkills[]
	// 0 ~ 10 �������� SelectNum���� ��ġ�� �ʴ� ������ �̱�
	bool SelectedSkills[static_cast<int>(ActiveType::MAX)] = { false, };
	int TrueCount = 0;
	while (TrueCount <= SelectNum)
	{
		int Index = Random.RandomInt(0, static_cast<int>(ActiveType::MAX));
		
		if (false == SelectedSkills[Index])
		{
			TrueCount++;
			SelectedSkills[Index] = true;
		}
	}



}

void LevelUpUI::Update()
{
	if (0 >= CreateCount_)
	{
		return;
	}


	// ������ ����
	if (true == GameEngineInput::GetInst()->IsDown("Num1"))
	{
		// �÷��̾�� ���� ����
		


		// ����
		Death();
		CreateCount_--;
		GameInfo::SetPause(false);
		IsActivated_ = false;
	}


}

void LevelUpUI::Render()
{
}
