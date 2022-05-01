#include "LevelUpUI.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <string>

#include "GameEnum.h"
#include "GameInfo.h"

#include "StatUI.h"

int LevelUpUI::CreateCount_ = 0;
bool LevelUpUI::IsActivated_ = false;
LevelUpUI::STATE LevelUpUI::State_ = STATE::NONE;

bool LevelUpUI::GetBox_ = false;


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
	BoxBackGround_ = CreateRenderer("LevelUpUI.bmp", static_cast<int>(RENDER_ORDER::UI));
	SetScale(BoxBackGround_->GetScale());
	BoxBackGround_->CameraEffectOff();
	BoxBackGround_->SetPivot(GameEngineWindow::GetScale().Half() + float4{0, 10});
	BoxBackGround_->Off();


	// ���� UI ���� Ŵ
	if (nullptr == StatUI_)
	{
		StatUI_ = GetLevel()->CreateActor<StatUI>(static_cast<int>(ACTOR_ORDER::UI), "UI");
	}
	else
	{
		StatUI_->On();
	}
	

	// ����
	GameEngineSound::SoundPlayOneShot("LevelUp.MP3", 0);
	IsActivated_ = true;


	// ��� ��ų������ �ִ���
	if (true == GameInfo::SkillLevelFull())
	{
		ChangeState(STATE::HPMONEY);
	}
	else
	{
		if (true == GetBox_)
		{
			ChangeState(STATE::TREASURE);
			EvolveSkill_ = GameInfo::SkillEvolveCheck();
			GetBox_ = false;
		}
		else
		{
			// ���� ���� ������ �Ϲ� 
			ChangeState(STATE::BOXES);
		}
	}

}

void LevelUpUI::Update()
{
	UpdateState();
}

void LevelUpUI::Render()
{
}


void LevelUpUI::SelectTreasure()
{

}

void LevelUpUI::ShowRandomSkills()
{
	if (0 >= SelectNum_)
	{
		int a = 0;
		return;
	}

	if (1 <= SelectNum_)
	{
		SkillType SelectSkill = RandomSkills_[0];
		Renderer1_->SetImage("LevelUp" + SkillTypeToName(SelectSkill) + ".bmp");
	}


	if (2 <= SelectNum_)
	{
		SkillType SelectSkill = RandomSkills_[1];
		Renderer2_->SetImage("LevelUp" + SkillTypeToName(SelectSkill) + ".bmp");
	}


	if (3 <= SelectNum_)
	{
		SkillType SelectSkill = RandomSkills_[2];
		Renderer3_->SetImage("LevelUp" + SkillTypeToName(SelectSkill) + ".bmp");
	}


	if (4 <= SelectNum_)
	{
		SkillType SelectSkill = RandomSkills_[3];
		Renderer4_->SetImage("LevelUp" + SkillTypeToName(SelectSkill) + ".bmp");
	}

	
}

void LevelUpUI::SelectSkillBox()
{
	// ������ ����
	if (true == GameEngineInput::GetInst()->IsDown("Num1") && SelectNum_ >= 1)
	{
		// �÷��̾�� ���� ���� ����
		SelectSkill(RandomSkills_[0]);

		RandomSkills_.clear();

		// ����
		Death();
		CreateCount_--;
		IsActivated_ = false;
		StatUI_->Off();
		return;
	}

	// ������ ����
	if (true == GameEngineInput::GetInst()->IsDown("Num2") && SelectNum_ >= 2)
	{
		// �÷��̾�� ���� ���� ����
		SelectSkill(RandomSkills_[1]);

		RandomSkills_.clear();

		// ����
		Death();
		CreateCount_--;
		IsActivated_ = false;
		StatUI_->Off();
		return;
	}

	// ������ ����
	if (true == GameEngineInput::GetInst()->IsDown("Num3") && SelectNum_ >= 3)
	{
		// �÷��̾�� ���� ���� ����
		SelectSkill(RandomSkills_[2]);

		RandomSkills_.clear();

		// ����
		Death();
		CreateCount_--;
		IsActivated_ = false;
		StatUI_->Off();
		return;
	}

	// ������ ����
	if (true == GameEngineInput::GetInst()->IsDown("Num4") && SelectNum_ >= 4)
	{
		// �÷��̾�� ���� ���� ����
		SelectSkill(RandomSkills_[3]);

		RandomSkills_.clear();

		// ����
		Death();
		CreateCount_--;
		IsActivated_ = false;
		StatUI_->Off();
		return;
	}
}

void LevelUpUI::SelectSkill(SkillType _SkillType)
{
	// ������ 0, ������ �߰�
	if (0 == GameInfo::GetPlayerInfo()->AllSkillLevel_[_SkillType])
	{

		if ( static_cast<int>(_SkillType) < ACTIVE_MAX)
		{
			GameInfo::GetPlayerInfo()->ActiveSkillSlot_.push_back(_SkillType);
		}
		else
		{
			GameInfo::GetPlayerInfo()->PassiveSkillSlot_.push_back(_SkillType);
		}

	}

	// ��ų������
	auto val = GameInfo::GetPlayerInfo()->AllSkillLevel_[_SkillType] += 1;

}


void LevelUpUI::UpdateState()
{
switch (State_)
{
case LevelUpUI::STATE::BOXES:
	BoxesUpdate();
	break;
case LevelUpUI::STATE::TREASURE:
	TreasureUpdate();
	break;
case LevelUpUI::STATE::TREASURE_OPENING:
	TreasureOpeningUpdate();
	break;
case LevelUpUI::STATE::TREASURE_END:
	TreasureEndingUpdate();
	break;
case LevelUpUI::STATE::HPMONEY:
	HpMoneyUpdate();
	break;
default:
	break;
}
}

void LevelUpUI::ChangeState(STATE _State)
{
	switch (_State)
	{
	case LevelUpUI::STATE::BOXES:
		BoxesStart();
		break;
	case LevelUpUI::STATE::TREASURE:
		TreasureStart();
		break;
	case LevelUpUI::STATE::TREASURE_OPENING:
		TreasureOpeningStart();
		break;
	case LevelUpUI::STATE::TREASURE_END:
		TreasureEndingStart();
		break;
	case LevelUpUI::STATE::HPMONEY:
		HpMoneyStart();
		break;
	default:
		break;
	}

	State_ = _State;
}

void LevelUpUI::BoxesStart()
{
	BoxBackGround_->On();

	// ���� ���� �ڽ� 1~4�� ��� ��ų(��Ƽ��/�нú�) ����
	SelectNum_ = 3;

	// ���� ���� �ڽ� 1
	Renderer1_ = CreateRenderer("LevelupBlank.bmp", static_cast<int>(RENDER_ORDER::UI));
	Renderer1_->CameraEffectOff();
	Renderer1_->SetPivot(GameEngineWindow::GetScale().Half() + float4{ 2, -Renderer1_->GetImageScale().y });


	// ���� ���� �ڽ� 2
	Renderer2_ = CreateRenderer("LevelupBlank.bmp", static_cast<int>(RENDER_ORDER::UI));
	Renderer2_->CameraEffectOff();
	Renderer2_->SetPivot(GameEngineWindow::GetScale().Half() + float4{ 2, 0 });

	// ���� ���� �ڽ� 3
	Renderer3_ = CreateRenderer("LevelupBlank.bmp", static_cast<int>(RENDER_ORDER::UI));
	Renderer3_->CameraEffectOff();
	Renderer3_->SetPivot(GameEngineWindow::GetScale().Half() + float4{ 2, Renderer1_->GetImageScale().y });

	// ���� ���� �ڽ� 4 ����� ����
	float PlayerLuck = GameInfo::GetPlayerInfo()->Luck_;
	PlayerLuck += 30;
	int Success = Random.RandomInt(1, 101);

	// ����
	if (Success <= PlayerLuck)
	{
		// ���� ���� �ڽ� 4
		Renderer4_ = CreateRenderer("LevelupBlank.bmp", static_cast<int>(RENDER_ORDER::UI));
		Renderer4_->CameraEffectOff();
		Renderer4_->SetPivot(GameEngineWindow::GetScale().Half() + float4{ 2, Renderer1_->GetImageScale().y * 2 });

		SelectNum_ = 4;
	}

	// �������� SelectNum���� ��ġ�� �ʴ� ������ �̱�
	bool SelectedSkills[static_cast<int>(SkillType::MAX)] = { false, };
	int TrueCount = 0;

	// SelectNum_ -> ���� ��ų�� 8������ �ƴ� ��ų�� ����
	int MaxLevelCount = 0;

	std::map<SkillType, int>::iterator FindIter = GameInfo::GetPlayerInfo()->AllSkillLevel_.begin();
	std::map<SkillType, int>::iterator EndIter = GameInfo::GetPlayerInfo()->AllSkillLevel_.end();
	for (; FindIter != EndIter; ++FindIter)
	{
		if ((*FindIter).first == SkillType::MAX)
		{
			break;
		}

		if (SKILL_LEVELMAX <= (*FindIter).second)
		{
			MaxLevelCount++;
		}
	}

	int SelectableCount = static_cast<int>(SkillType::MAX) - MaxLevelCount;
	if (SelectableCount < SelectNum_)
	{
		SelectNum_ = SelectableCount;
	}



	while (TrueCount < SelectNum_)
	{
		int Index = Random.RandomInt(0, static_cast<int>(SkillType::MAX) - 1);

		// 8���� �̸� ��ų�鸸 ��
		if (false == SelectedSkills[Index] && GameInfo::GetPlayerInfo()->AllSkillLevel_[(SkillType)Index] < SKILL_LEVELMAX)
		{
			// ��ų����(Active/Passive)�� 6�� �� ���� ���� �� ����
			// Active
			if (Index < ACTIVE_MAX && 6 <= static_cast<int>(GameInfo::GetPlayerInfo()->ActiveSkillSlot_.size()))
			{
				continue;
			}
			// Passive
			if (Index >= ACTIVE_MAX && 6 <= static_cast<int>(GameInfo::GetPlayerInfo()->PassiveSkillSlot_.size()))
			{
				continue;
			}

			TrueCount++;
			SelectedSkills[Index] = true;

			// 3~4���� �ڽ� UI�� �ø� ���� ����
			RandomSkills_.push_back((SkillType)Index);
		}
	}

	ShowRandomSkills();
}

void LevelUpUI::BoxesUpdate()
{
	SelectSkillBox();
}

void LevelUpUI::TreasureStart()
{
	// ��������
	GameEngineSound::SoundPlayOneShot("TreasureFound.mp3", 0);
	BoxAnim_ = CreateRenderer("BoxFound.bmp", static_cast<int>(RENDER_ORDER::UI));
	BoxAnim_->CameraEffectOff();
	BoxAnim_->SetPivot(GameEngineWindow::GetScale().Half() + float4{ 0, 10 });
	BoxAnim_->CreateAnimation("Box_Bounce.bmp", "Box_Bounce", 0, 89, 0.025f, true);
	BoxAnim_->CreateAnimation("Box_Opening.bmp", "Box_Opening", 0, 209, 0.025f, false);
	BoxAnim_->CreateAnimation("Box_Ending.bmp", "Box_Ending", 0, 172, 0.025f, false);
	BoxAnim_->CreateAnimation("Box_End.bmp", "Box_End", 0, 132, 0.025f, true);
	BoxAnim_->ChangeAnimation("Box_Bounce");

	// Treasure
	Treasure_ = CreateRenderer("Box_ThousandEdge.bmp", static_cast<int>(RENDER_ORDER::UI2));
	Treasure_->CameraEffectOff();
	Treasure_->Off();
	Treasure_->SetPivot(GameEngineWindow::GetScale().Half() + float4{ 0, 10 });

	TreasureOnCounter_.SetCount(6.5f);
}

void LevelUpUI::TreasureUpdate()
{
	if (true == GameEngineInput::GetInst()->IsDown("SpaceBar"))
	{
		ChangeState(STATE::TREASURE_OPENING);
	}
}

void LevelUpUI::TreasureOpeningStart()
{
	GameEngineSound::SoundPlayOneShot("TreasureOpening.mp3", 0);
	BoxAnim_->ChangeAnimation("Box_Opening");
}

void LevelUpUI::TreasureOpeningUpdate()
{
	// ���߿� ���� ���
	if (true == TreasureOnCounter_.Start(GameEngineTime::GetDeltaTime()))
	{
		Treasure_->On();
	}

	if (true == BoxAnim_->IsEndAnimation())
	{
		ChangeState(STATE::TREASURE_END);
	}
}

void LevelUpUI::TreasureEndingStart()
{
	BoxAnim_->ChangeAnimation("Box_Ending");
}

void LevelUpUI::TreasureEndingUpdate()
{
	if (true == BoxAnim_->IsEndAnimation())
	{
		BoxAnim_->ChangeAnimation("Box_End");
	}

	if (true == GameEngineInput::GetInst()->IsDown("SpaceBar"))
	{
		// ���� ȹ�� (�������� or �Ϲݹ���)
		//GameInfo::ChangeEvolvedSkill(EvolveSkill_);
		UIEnd();
	}
}


void LevelUpUI::HpMoneyStart()
{

}



void LevelUpUI::HpMoneyUpdate()
{

}

void LevelUpUI::UIEnd()
{
	Death();
	CreateCount_--;
	IsActivated_ = false;
	GetBox_ = false;
	StatUI_->Off();
	return;
}
