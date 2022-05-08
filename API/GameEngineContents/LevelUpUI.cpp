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
	: EvolveSkill_(SkillType::NONE)
{

}

LevelUpUI::~LevelUpUI() 
{
}

void LevelUpUI::Start()
{
	NextLevelOff();

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

	// �ڽ� ����
	if (true == GetBox_)
	{
		EvolveSkill_ = GameInfo::SkillEvolveCheck();

		// ��ų�� �� ���� �ʾҴٸ�(��������)
		bool Full = GameInfo::EvolveSkillLevelFull();

		if (false == Full)
		{
			ChangeState(STATE::TREASURE);
		}
		else
		{
			// �� á�ٸ�
			if (SkillType::NONE != EvolveSkill_)
			{
				ChangeState(STATE::TREASURE);
			}
			else
			{
				ChangeState(STATE::HPMONEY);
			}
		}

	}
	// ������
	else
	{
		if (true == GameInfo::SkillLevelFull())
		{
			ChangeState(STATE::HPMONEY);
		}
		else
		{
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



void LevelUpUI::ShowRandomSkills()
{
	if (0 >= SelectNum_)
	{
		MsgBoxAssert("�߸��� LevelUPUI�б�� ���Խ��ϴ�");
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
		UIEnd();
		return;
	}

	// ������ ����
	if (true == GameEngineInput::GetInst()->IsDown("Num2") && SelectNum_ >= 2)
	{
		// �÷��̾�� ���� ���� ����
		SelectSkill(RandomSkills_[1]);

		RandomSkills_.clear();

		// ����
		UIEnd();
		return;
	}

	// ������ ����
	if (true == GameEngineInput::GetInst()->IsDown("Num3") && SelectNum_ >= 3)
	{
		// �÷��̾�� ���� ���� ����
		SelectSkill(RandomSkills_[2]);

		RandomSkills_.clear();

		// ����
		UIEnd();
		return;
	}

	// ������ ����
	if (true == GameEngineInput::GetInst()->IsDown("Num4") && SelectNum_ >= 4)
	{
		// �÷��̾�� ���� ���� ����
		SelectSkill(RandomSkills_[3]);

		RandomSkills_.clear();

		// ����
		UIEnd();
		return;
	}
}

void LevelUpUI::SelectSkill(SkillType _SkillType)
{
	std::map<SkillType, int>& AllSkillLevel = GameInfo::GetPlayerInfo()->AllSkillLevel_;

	// ���ο� ��ų
	if ( 0 == AllSkillLevel[_SkillType])
	{
		if (ACTIVE_MAX > static_cast<int>(_SkillType))
		{
			GameInfo::GetPlayerInfo()->ActiveSkillSlot_.push_back(_SkillType);
		}
		else if (ACTIVE_MAX <= static_cast<int>(_SkillType) && SkillType::MAX > _SkillType)
		{
			GameInfo::GetPlayerInfo()->PassiveSkillSlot_.push_back(_SkillType);
		}

		AllSkillLevel[_SkillType] = 1;
	}
	else
	{
		// �̹� �ִ� ��ų ������
		AllSkillLevel[_SkillType] += 1;
	}
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
	GameInfo::GetPlayerInfo()->Luck_ += GameInfo::GetPlayerInfo()->AllSkillLevel_[SkillType::CLOVER] * 3;
	float PlayerLuck = GameInfo::GetPlayerInfo()->Luck_;
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

	// SelectNum_Ȯ��
	int MaxLevelCount = 0;

	std::map<SkillType, int>::iterator FindIter = GameInfo::GetPlayerInfo()->AllSkillLevel_.begin();
	std::map<SkillType, int>::iterator EndIter = GameInfo::GetPlayerInfo()->AllSkillLevel_.end();
	for (; FindIter != EndIter; ++FindIter)
	{
		if ((*FindIter).first == SkillType::MAX)
		{
			break;
		}

		if (SKILL_LEVELMAX <= (*FindIter).second || -1 == (*FindIter).second)
		{
			MaxLevelCount++;
		}
	}

	int SelectableCount = static_cast<int>(SkillType::MAX) - MaxLevelCount;
	if (SelectableCount < SelectNum_)
	{
		SelectNum_ = SelectableCount;
	}


	std::set<SkillType> Skills;
	// RandomSkills_�� SelectNum��ŭ�� ��ų Push
	// ���� �� �ִ� ��ų : 0���� && -1����X 
	while (Skills.size() < SelectNum_)
	{
		SkillType Skill = SelectBoxSkills();
		if (SkillType::NONE != Skill)
		{
			Skills.insert(Skill);
		}
	}

	for (SkillType Skill : Skills)
	{
		RandomSkills_.push_back(Skill);
	}
	Skills.clear();
	
	ShowRandomSkills();
}

void LevelUpUI::BoxesUpdate()
{
	SelectSkillBox();
}

void LevelUpUI::TreasureStart()
{
	SelectedTreasure_ = SelectTreasure();

	if (SkillType::NONE == SelectedTreasure_)
	{
		ChangeState(STATE::BOXES);
	}

	// ��������
	GameEngineSound::SoundPlayOneShot("TreasureFound.mp3", 0);
	BoxAnim_ = CreateRenderer("BoxFound.bmp", static_cast<int>(RENDER_ORDER::UI));
	BoxAnim_->CameraEffectOff();
	BoxAnim_->SetPivot(GameEngineWindow::GetScale().Half() + float4{ 0, 10 });
	BoxAnim_->CreateAnimation("Box_Bounce.bmp", "Box_Bounce", 0, 89, 0.025f, true);
	BoxAnim_->CreateAnimation("Box_Opening.bmp", "Box_Opening", 0, 209, 0.025f, false);
	BoxAnim_->CreateAnimation("Box_Ending.bmp", "Box_Ending", 0, 172, 0.025f, false);
	BoxAnim_->CreateAnimation("Box_End.bmp", "Box_End", 0, 132, 0.025f, false);
	BoxAnim_->ChangeAnimation("Box_Bounce");

	// Treasure
	Treasure_ = CreateRenderer("Box_" + SkillTypeToName(SelectedTreasure_) + ".bmp", static_cast<int>(RENDER_ORDER::UI2));

	Treasure_->CameraEffectOff();
	Treasure_->Off();
	Treasure_->SetPivot(GameEngineWindow::GetScale().Half() + float4{ 0, 10 });

	TreasureOnCounter_.SetCount(6.10f);
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

		if (true == BoxAnim_->IsEndAnimation())
		{
			ChangeState(STATE::TREASURE_END);
		}
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
		// ���� ȹ�� 
		if (SkillType::NONE != EvolveSkill_)
		{
			GameInfo::PushEvolvedSkill(EvolveSkill_);
		}
		else
		{
			SelectSkill(SelectedTreasure_);
		}

		UIEnd();
	}
}


void LevelUpUI::HpMoneyStart()
{
	BoxBackGround_->On();

	HpRenderer_ = CreateRenderer("LevelUpHp.bmp", static_cast<int>(RENDER_ORDER::UI));
	HpRenderer_->CameraEffectOff();
	HpRenderer_->SetPivot(GameEngineWindow::GetScale().Half() + float4{ 2, -HpRenderer_->GetImageScale().y });
	MoneyRenderer_ = CreateRenderer("LevelUpMoney.bmp", static_cast<int>(RENDER_ORDER::UI));
	MoneyRenderer_->CameraEffectOff();
	MoneyRenderer_->SetPivot(GameEngineWindow::GetScale().Half() + float4{ 2, 2 });
}

void LevelUpUI::HpMoneyUpdate()
{
	if (true == GameEngineInput::GetInst()->IsDown("Num1"))
	{
		GameInfo::GetPlayerInfo()->CurrentHp_ += 30;
		if (GameInfo::GetPlayerInfo()->CurrentHp_ > 100)
		{
			float OverHp = GameInfo::GetPlayerInfo()->CurrentHp_ - 100;
			GameInfo::GetPlayerInfo()->CurrentHp_ = 100;
			GameInfo::GetPlayerInfo()->MaxHp_ += OverHp;
		}
		UIEnd();
	}

	if (true == GameEngineInput::GetInst()->IsDown("Num2"))
	{
		GameInfo::GetPlayerInfo()->EearnedCoin_ += 25;
		UIEnd();
	}
}


SkillType LevelUpUI::SelectTreasure()
{
	// Evolve �� �� �ִ� Skill �� ������ �� ��ų ����
	if (SkillType::NONE != EvolveSkill_)
	{
		return EvolveSkill_;
	}
	else
	{
		// �ƴ϶�� ������ "��ų" + �ƽ������� ������ �ȵ� + -1������ ������ �ȵ�
		std::vector<SkillType> Treasures;

		// ���� 8 �̸� -1�ƴ� ���� �� �ִ� ��ų �߰�
		// ��Ƽ�� ������ �������� ������ �߰�
		std::map<SkillType, int>& AllSkillLevel = GameInfo::GetPlayerInfo()->AllSkillLevel_;

		for (int i = 0; i < ACTIVE_MAX; i++)
		{
			SkillType Type = static_cast<SkillType>(i);

			if (8 > AllSkillLevel[Type] && -1 != AllSkillLevel[Type])
			{
				Treasures.push_back(Type);
			}
		}

		// ���� ��ų 1���� �̻�����
		for (int i = static_cast<int>(SkillType::MAX) + 1; i < EVOLVE_MAX; i++)
		{
			SkillType Type = static_cast<SkillType>(i);

			if (8 > AllSkillLevel[Type] && 1 <= AllSkillLevel[Type])
			{
				Treasures.push_back(Type);
			}
		}

		// ��ų�� ��� 8����, �ø��� �нú� ��ų �ۿ� ���ٸ�
		if (0 == Treasures.size())
		{
			return SkillType::NONE;
		}

		int Index = Random.RandomInt(0, static_cast<int>(Treasures.size()) - 1);
		return Treasures[Index];
	}

}

SkillType LevelUpUI::SelectBoxSkills()
{
	std::vector<SkillType> BoxSkills;

	// ���� 8 �̸� -1�ƴ� ���� �� �ִ� ��ų �߰�
	std::map<SkillType, int>& AllSkillLevel = GameInfo::GetPlayerInfo()->AllSkillLevel_;

	for (int i = 0; i < static_cast<int>(SkillType::MAX); i++)
	{
		SkillType Type = static_cast<SkillType>(i);

		if (8 > AllSkillLevel[Type] && -1 != AllSkillLevel[Type])
		{
			BoxSkills.push_back(Type);
		}
	}

	// ��ų�� ��� 8����, �ø��� �нú� ��ų �ۿ� ���ٸ�
	if (0 == BoxSkills.size())
	{
		return SkillType::NONE;
	}

	// ���� ��ų ����
	int Index = Random.RandomInt(0, static_cast<int>(BoxSkills.size()) - 1);
	return BoxSkills[Index];
}

void LevelUpUI::UIEnd()
{
	Death();
	CreateCount_--;
	IsActivated_ = false;
	GetBox_ = false;
	SelectedTreasure_ = SkillType::NONE;
	BoxBackGround_->Off();
	StatUI_->Off();
	RandomSkills_.clear();
	return;
}
