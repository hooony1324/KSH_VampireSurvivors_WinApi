#include "LevelUpUI.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <string>

#include "ObjectEnum.h"
#include "GameInfo.h"

int LevelUpUI::CreateCount_ = 0;
bool LevelUpUI::IsActivated_ = false;

std::string SkillBoxUI[] = 
{
	"LevelupKnife.bmp", "LevelupMagicwand.bmp", "LevelupFirewand.bmp", "LevelupRunetracer.bmp",
	"LevelupAxe.bmp", "LevelupClocklancet.bmp", "LevelupCross.bmp", "LevelupBible.bmp",
	"LevelupWhip.bmp", "LevelupGarlic.bmp", "LevelupLaurel.bmp", "LevelupLightening.bmp",
	"LevelupHolywater.bmp", "LevelupFiveStar.bmp", "LevelupBracer.bmp", "LevelupEmptytome.bmp",
	"LevelupSpinach.bmp", "LevelupSpellbinder.bmp", "LevelupHollowheart.bmp", "LevelupClover.bmp",
	"LevelupPummarola.bmp", "LevelupCandle.bmp", "LevelupWing.bmp"
};

LevelUpUI::LevelUpUI() 
{
	RandomSkills_.reserve(4);
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


	// ���� ���� �ڽ� 1~4�� ��� ��ų(��Ƽ��/�нú�) ����

	SelectNum_ = 3;
	// ���� ���� �ڽ� 1
	Renderer1_ = CreateRenderer();
	Renderer1_->SetImage("LevelupBlank.bmp");
	Renderer1_->CameraEffectOff();
	Renderer1_->SetPivot(GameEngineWindow::GetScale().Half() + float4{2, -Renderer1_->GetImageScale().y});
	

	// ���� ���� �ڽ� 2
	Renderer2_ = CreateRenderer();
	Renderer2_->SetImage("LevelupBlank.bmp");
	Renderer2_->CameraEffectOff();
	Renderer2_->SetPivot(GameEngineWindow::GetScale().Half() + float4{ 2, 0 });

	// ���� ���� �ڽ� 3
	Renderer3_ = CreateRenderer();
	Renderer3_->SetImage("LevelupBlank.bmp");
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
		Renderer4_->SetImage("LevelupBlank.bmp");
		Renderer4_->CameraEffectOff();
		Renderer4_->SetPivot(GameEngineWindow::GetScale().Half() + float4{ 2, Renderer1_->GetImageScale().y * 2 });

		SelectNum_ = 4;
	}

	// �߿� : ó���� 0 ~ 10 ������ ���߿��� ���� ��ų�� ���¿� ���� ���� �� �ִ� ��ų�迭�� �޶����� �� ex. SelectableSkills[]
	// 0 ~ 10 �������� SelectNum���� ��ġ�� �ʴ� ������ �̱�
	bool SelectedSkills[static_cast<int>(SkillType::MAX)] = { false, };
	int TrueCount = 0;

	// ��ų �������� üũ
	int Count = GameInfo::GetPlayerInfo()->ActivatedSkillsCount_;
	int Spare = SKILL_LEVELMAX - Count;
	if (Spare < SelectNum_)
	{
		SelectNum_ = Spare;
	}

	while (TrueCount <= SelectNum_)
	{
		int Index = Random.RandomInt(0, static_cast<int>(SkillType::MAX));
		
		if (false == SelectedSkills[Index] && GameInfo::GetPlayerInfo()->SkillLevelInfo_[Index] < SKILL_LEVELMAX)
		{
			TrueCount++;
			SelectedSkills[Index] = true;

			// 3~4���� �ڽ� UI�� �ø� ���� ����
			RandomSkills_.push_back(Index);
		}
	}



	ShowRandomSkills();


}

void LevelUpUI::Update()
{
	if (0 >= CreateCount_)
	{
		return;
	}


	// ������ ����
	if (true == GameEngineInput::GetInst()->IsDown("Num1") && SelectNum_ >= 1)
	{
		// �÷��̾�� ���� ���� ����
		

		// GameInfo::GetPlayerInfo()->ActivatedSkillsCount_ ++;
		RandomSkills_.clear();

		// ����
		Death();
		CreateCount_--;
		GameInfo::SetPause(false);
		IsActivated_ = false;
		return;
	}

	// ������ ����
	if (true == GameEngineInput::GetInst()->IsDown("Num2") && SelectNum_ >= 2)
	{
		// �÷��̾�� ���� ���� ����


		// GameInfo::GetPlayerInfo()->ActivatedSkillsCount_ ++;
		RandomSkills_.clear();

		// ����
		Death();
		CreateCount_--;
		GameInfo::SetPause(false);
		IsActivated_ = false;
		return;
	}

	// ������ ����
	if (true == GameEngineInput::GetInst()->IsDown("Num3") && SelectNum_ >= 3)
	{
		// �÷��̾�� ���� ���� ����


		// GameInfo::GetPlayerInfo()->ActivatedSkillsCount_ ++;
		RandomSkills_.clear();

		// ����
		Death();
		CreateCount_--;
		GameInfo::SetPause(false);
		IsActivated_ = false;
		return;
	}

	// ������ ����
	if (true == GameEngineInput::GetInst()->IsDown("Num4") && SelectNum_ >= 4)
	{
		// �÷��̾�� ���� ���� ����


		// GameInfo::GetPlayerInfo()->ActivatedSkillsCount_ ++;
		RandomSkills_.clear();

		// ����
		Death();
		CreateCount_--;
		GameInfo::SetPause(false);
		IsActivated_ = false;
		return;
	}


}

void LevelUpUI::Render()
{
}

void LevelUpUI::ShowRandomSkills()
{
	if (0 >= SelectNum_)
	{
		return;
	}

	if (1 <= SelectNum_)
	{
		int SelectSkill = RandomSkills_[0];
		Renderer1_->SetImage(SkillBoxUI[SelectSkill]);
	}


	if (2 <= SelectNum_)
	{
		int SelectSkill = RandomSkills_[1];
		Renderer2_->SetImage(SkillBoxUI[SelectSkill]);
	}


	if (3 <= SelectNum_)
	{
		int SelectSkill = RandomSkills_[2];
		Renderer3_->SetImage(SkillBoxUI[SelectSkill]);
	}


	if (4 <= SelectNum_)
	{
		int SelectSkill = RandomSkills_[3];
		Renderer4_->SetImage(SkillBoxUI[SelectSkill]);
	}

	
}
