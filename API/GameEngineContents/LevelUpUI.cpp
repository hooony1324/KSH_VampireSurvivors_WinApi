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

LevelUpUI::LevelUpUI() 
{
	RandomSkills_.reserve(4);

}

LevelUpUI::~LevelUpUI() 
{
}

void LevelUpUI::Start()
{


	// 배경 
	GameEngineRenderer* Renderer = CreateRenderer("LevelUpUI.bmp");
	SetScale(Renderer->GetScale());
	Renderer->CameraEffectOff();
	Renderer->SetPivot(GameEngineWindow::GetScale().Half() + float4{0, 10});

	if (nullptr == StatUI_)
	{
		StatUI_ = GetLevel()->CreateActor<StatUI>(static_cast<int>(ACTOR_ORDER::UI), "UI");
	}
	else
	{
		StatUI_->On();
	}
	


	// 사운드
	GameEngineSound::SoundPlayOneShot("LevelUp.MP3", 0);
	GameInfo::SetPause(true);
	IsActivated_ = true;


	// 무기 선택 박스 1~4에 띄울 스킬(액티브/패시브) 선택
	SelectNum_ = 3;

	// 무기 선택 박스 1
	Renderer1_ = CreateRenderer();
	Renderer1_->SetImage("LevelupBlank.bmp");
	Renderer1_->CameraEffectOff();
	Renderer1_->SetPivot(GameEngineWindow::GetScale().Half() + float4{2, -Renderer1_->GetImageScale().y});
	

	// 무기 선택 박스 2
	Renderer2_ = CreateRenderer();
	Renderer2_->SetImage("LevelupBlank.bmp");
	Renderer2_->CameraEffectOff();
	Renderer2_->SetPivot(GameEngineWindow::GetScale().Half() + float4{ 2, 0 });

	// 무기 선택 박스 3
	Renderer3_ = CreateRenderer();
	Renderer3_->SetImage("LevelupBlank.bmp");
	Renderer3_->CameraEffectOff();
	Renderer3_->SetPivot(GameEngineWindow::GetScale().Half() + float4{ 2, Renderer1_->GetImageScale().y });

	// 무기 선택 박스 4 띄울지 여부
	float PlayerLuck = GameInfo::GetPlayerInfo()->Luck_;
	//PlayerLuck = 30;
	GameEngineRandom Random;
	int Success = Random.RandomInt(1, 101);
	
	// 성공
	if (Success <= PlayerLuck)
	{
		// 무기 선택 박스 4
		Renderer4_ = CreateRenderer();
		Renderer4_->SetImage("LevelupBlank.bmp");
		Renderer4_->CameraEffectOff();
		Renderer4_->SetPivot(GameEngineWindow::GetScale().Half() + float4{ 2, Renderer1_->GetImageScale().y * 2 });

		SelectNum_ = 4;
	}

	// 중요 : 처음엔 0 ~ 10 이지만 나중에는 뽑은 스킬의 상태에 따라 뽑을 수 있는 스킬배열이 달라져야 함 ex. SelectableSkills[]
	// 0 ~ 10 연속으로 SelectNum개의 겹치지 않는 랜덤수 뽑기
	bool SelectedSkills[static_cast<int>(SkillType::MAX)] = { false, };
	int TrueCount = 0;

	// 스킬 여유공간 체크
	int Count = static_cast<int>(SkillType::MAX)
		- (static_cast<int>(GameInfo::GetPlayerInfo()->ActiveSkillSlot_.size()) + static_cast<int>(GameInfo::GetPlayerInfo()->PassiveSkillSlot_.size()));
	int Spare = SKILL_LEVELMAX - Count;
	if (Spare < SelectNum_)
	{
		SelectNum_ = Spare;
	}

	while (TrueCount < SelectNum_)
	{
		int Index = Random.RandomInt(0, static_cast<int>(SkillType::MAX) - 1);
		if (Index == static_cast<int>(SkillType::MAX) || Index == static_cast<int>(SkillType::MAX))
		{
			continue;
		}

		// 8레벨 미만 스킬들만 고름
		if (false == SelectedSkills[Index] && GameInfo::GetPlayerInfo()->SkillLevelInfo_[Index] < SKILL_LEVELMAX)
		{
			TrueCount++;
			SelectedSkills[Index] = true;

			// 3~4개의 박스 UI에 올릴 무기 선택
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

	if (0 < SelectNum_)
	{
		SelectSkillBox();
		return;
	}

	SelectHpMoneyBox();


}

void LevelUpUI::Render()
{
}

void LevelUpUI::ShowRandomSkills()
{
	if (0 >= SelectNum_)
	{
		// 돈 또는 체력 선택
		return;
	}

	if (1 <= SelectNum_)
	{
		int SelectSkill = RandomSkills_[0];
		Renderer1_->SetImage("LevelUp" + SkillOrder[SelectSkill] + ".bmp");
	}


	if (2 <= SelectNum_)
	{
		int SelectSkill = RandomSkills_[1];
		Renderer2_->SetImage("LevelUp" + SkillOrder[SelectSkill] + ".bmp");
	}


	if (3 <= SelectNum_)
	{
		int SelectSkill = RandomSkills_[2];
		Renderer3_->SetImage("LevelUp" + SkillOrder[SelectSkill] + ".bmp");
	}


	if (4 <= SelectNum_)
	{
		int SelectSkill = RandomSkills_[3];
		Renderer4_->SetImage("LevelUp" + SkillOrder[SelectSkill] + ".bmp");
	}

	
}

void LevelUpUI::SelectSkillBox()
{
	// 아이템 선택
	if (true == GameEngineInput::GetInst()->IsDown("Num1") && SelectNum_ >= 1)
	{
		// 플레이어에게 무기 정보 갱신
		SelectSkill(RandomSkills_[0]);

		RandomSkills_.clear();


		// 종료
		Death();
		CreateCount_--;
		GameInfo::SetPause(false);
		IsActivated_ = false;
		StatUI_->Off();
		return;
	}

	// 아이템 선택
	if (true == GameEngineInput::GetInst()->IsDown("Num2") && SelectNum_ >= 2)
	{
		// 플레이어에게 무기 정보 갱신
		SelectSkill(RandomSkills_[1]);

		RandomSkills_.clear();

		// 종료
		Death();
		CreateCount_--;
		GameInfo::SetPause(false);
		IsActivated_ = false;
		StatUI_->Off();
		return;
	}

	// 아이템 선택
	if (true == GameEngineInput::GetInst()->IsDown("Num3") && SelectNum_ >= 3)
	{
		// 플레이어에게 무기 정보 갱신
		SelectSkill(RandomSkills_[2]);

		RandomSkills_.clear();

		// 종료
		Death();
		CreateCount_--;
		GameInfo::SetPause(false);
		IsActivated_ = false;
		StatUI_->Off();
		return;
	}

	// 아이템 선택
	if (true == GameEngineInput::GetInst()->IsDown("Num4") && SelectNum_ >= 4)
	{
		// 플레이어에게 무기 정보 갱신
		SelectSkill(RandomSkills_[3]);

		RandomSkills_.clear();

		// 종료
		Death();
		CreateCount_--;
		GameInfo::SetPause(false);
		IsActivated_ = false;
		StatUI_->Off();
		return;
	}
}

void LevelUpUI::SelectSkill(int _SkillNumber)
{
	// SkillSlot에 있는지 확인
	// 없으면 추가
	// 있으면 스킬레벨업
	GameInfo::GetPlayerInfo()->ActiveSkillSlot_;
	GameInfo::GetPlayerInfo()->PassiveSkillSlot_;

	int SkillLevel = GameInfo::GetPlayerInfo()->SkillLevelInfo_[_SkillNumber];


	if (0 == SkillLevel)
	{
		SkillType Type = static_cast<SkillType>(_SkillNumber);

		if (_SkillNumber < ACTIVE_MAX)
		{
			GameInfo::GetPlayerInfo()->ActiveSkillSlot_.push_back(Type);
		}
		else
		{
			GameInfo::GetPlayerInfo()->PassiveSkillSlot_.push_back(Type);
		}

	}
	
	GameInfo::GetPlayerInfo()->SkillLevelInfo_[_SkillNumber] += 1;

	
}

void LevelUpUI::SelectHpMoneyBox()
{

}