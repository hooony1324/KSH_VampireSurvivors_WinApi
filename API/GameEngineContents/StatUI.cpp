#include "StatUI.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>

#include "GameInfo.h"
#include <string>


StatUI::StatUI()
	: ActiveSkillCount_(1)
	, PassiveSkillCount_(0)
{
}

StatUI::~StatUI() 
{
}

void StatUI::Start()
{
	NextLevelOff();

	SetPosition(float4{8, 40});
	GameEngineRenderer* RendererBack = CreateRenderer("StatUI.bmp", static_cast<int>(RENDER_ORDER::UI));
	GameEngineRenderer* RendererText = CreateRenderer("StatUIText.bmp", static_cast<int>(RENDER_ORDER::UI));


	SetScale(RendererBack->GetScale());
	RendererBack->SetAlpha(100);
	RendererBack->CameraEffectOff();
	RendererBack->SetPivot(RendererBack->GetScale().Half());

	RendererText->CameraEffectOff();
	RendererText->SetPivot(RendererText->GetScale().Half());

	SetSlotBase();

	TextFont_.Load("../Resources/PlayUI/KO.ttf");

}

void StatUI::Update()
{
	SlotUpdate();
	


}

void StatUI::Render()
{
	TextDraw();
}


void StatUI::SlotUpdate()
{
	// 액티브
	std::vector<SkillType> ActiveSkillSlot = GameInfo::GetPlayerInfo()->ActiveSkillSlot_;
	ActiveSkillCount_ = ActiveSkillSlot.size();
	for (int i = 0; i < ActiveSkillCount_; i++)
	{
		ActiveSlots_[i]->On();
		ActiveSkills_[i]->On();
		ActiveLevels_[i]->On();
		int SkillType = static_cast<int>(ActiveSkillSlot[i]);
		ActiveSkills_[i]->SetImage(SkillOrder[SkillType] + "UI.bmp");

		int SkillLevel = GameInfo::GetPlayerInfo()->SkillLevelInfo_[SkillType];
		ActiveLevels_[i]->SetImage("WeaponLevel_" + std::to_string(SkillLevel) + ".bmp");
	}


	// 패시브
	std::vector<SkillType> PassiveSkillSlot = GameInfo::GetPlayerInfo()->PassiveSkillSlot_;
	PassiveSkillCount_ = PassiveSkillSlot.size();
	for (int i = 0; i < PassiveSkillCount_; i++)
	{
		PassiveSlots_[i]->On();
		PassiveSkills_[i]->On();
		PassiveLevels_[i]->On();
		int SkillType = static_cast<int>(PassiveSkillSlot[i]);
		PassiveSkills_[i]->SetImage(SkillOrder[SkillType] + "UI.bmp");

		int SkillLevel = GameInfo::GetPlayerInfo()->SkillLevelInfo_[SkillType];
		PassiveLevels_[i]->SetImage("WeaponLevel_" + std::to_string(SkillLevel) + ".bmp");
	}

}

void StatUI::SetSlotBase()
{
	for (int i = 0; i < 6; i++)
	{
		GameEngineRenderer* SlotPtr = CreateRenderer("WeaponBG.bmp", static_cast<int>(RENDER_ORDER::UI));
		GameEngineRenderer*	SkillPtr = CreateRenderer("KnifeUI.bmp", static_cast<int>(RENDER_ORDER::UI));
		GameEngineRenderer* LevelPtr = CreateRenderer("WeaponLevel_1.bmp", static_cast<int>(RENDER_ORDER::UI));

		SlotPtr->SetAlpha(100);
		SlotPtr->CameraEffectOff();
		SlotPtr->SetPivot(float4{ 28, 35 } + float4{ (static_cast<float>(i) * 30) + (static_cast<float>(i) * 6), 0 });
		SlotPtr->Off();

		SkillPtr->CameraEffectOff();
		SkillPtr->SetPivot(float4{ 28, 35 } + float4{ (static_cast<float>(i) * 30) + (static_cast<float>(i) * 6), 0 });
		SkillPtr->Off();

		LevelPtr->CameraEffectOff();
		LevelPtr->SetPivot(float4{ 28, 68 } + float4{ (static_cast<float>(i) * 30) + (static_cast<float>(i) * 6), 0 });
		LevelPtr->Off();

		ActiveSlots_.push_back(SlotPtr);
		ActiveSkills_.push_back(SkillPtr);
		ActiveLevels_.push_back(LevelPtr);
	}

	for (int i = 0; i < 6; i++)
	{
		GameEngineRenderer* SlotPtr = CreateRenderer("WeaponBG.bmp", static_cast<int>(RENDER_ORDER::UI));
		GameEngineRenderer* SkillPtr = CreateRenderer("KnifeUI.bmp", static_cast<int>(RENDER_ORDER::UI));
		GameEngineRenderer* LevelPtr = CreateRenderer("WeaponLevel_1.bmp", static_cast<int>(RENDER_ORDER::UI));

		SlotPtr->SetAlpha(100);
		SlotPtr->CameraEffectOff();
		SlotPtr->SetPivot(float4{ 28, 102} + float4{ (static_cast<float>(i) * 30) + (static_cast<float>(i) * 6), 0 });
		SlotPtr->Off();

		SkillPtr->CameraEffectOff();
		SkillPtr->SetPivot(float4{ 28, 102 } + float4{ (static_cast<float>(i) * 30) + (static_cast<float>(i) * 6), 0 });
		SkillPtr->Off();

		LevelPtr->CameraEffectOff();
		LevelPtr->SetPivot(float4{ 28, 135 } + float4{ (static_cast<float>(i) * 30) + (static_cast<float>(i) * 6), 0 });
		LevelPtr->Off();

		PassiveSlots_.push_back(SlotPtr);
		PassiveSkills_.push_back(SkillPtr);
		PassiveLevels_.push_back(LevelPtr);
	}

	// 처음에 주어진 스킬은 활성화
	ActiveSlots_[0]->On();
	ActiveSkills_[0]->On();
	ActiveLevels_[0]->On();

	SkillType SkillType = GameInfo::GetPlayerInfo()->ActiveSkillSlot_[0];
	ActiveSkills_[0]->SetImage(SkillOrder[static_cast<int>(SkillType)] + "UI.bmp");
}


void StatUI::TextDraw()
{

	float TextWidth = 8;
	float Space;
	float TextX = 228.0f;
	std::string Stat;

	float FirstY = 200;
	float FirstHeight = 19;
	Stat = std::to_string((int)GameInfo::GetPlayerInfo()->MaxHp_);
	Space = static_cast<int>(Stat.length()) * TextWidth;
	TextFont_.Draw(Stat, { TextX - Space, FirstY }, RGB(255, 255, 255), 20, 800);

	Stat = std::to_string((int)GameInfo::GetPlayerInfo()->Recovery_);
	Space = static_cast<int>(Stat.length()) * TextWidth;
	TextFont_.Draw(Stat, { TextX - Space, FirstY + FirstHeight * 1 }, RGB(255, 255, 255), 20, 800);

	Stat = std::to_string((int)GameInfo::GetPlayerInfo()->Guard_);
	Space = static_cast<int>(Stat.length()) * TextWidth;
	TextFont_.Draw(Stat, { TextX - Space, FirstY + FirstHeight * 2 }, RGB(255, 255, 255), 20, 800);

	Stat = std::to_string((int)GameInfo::GetPlayerInfo()->Speed_);
	Space = static_cast<int>(Stat.length()) * TextWidth;
	TextFont_.Draw(Stat + "%", {TextX - Space - 8, FirstY + FirstHeight * 3}, RGB(255, 255, 255), 20, 800);


	float SecondY = 297.0f;
	float SecondHeight = 19;
	Stat = std::to_string((int)GameInfo::GetPlayerInfo()->Power_);
	Space = static_cast<int>(Stat.length()) * TextWidth;
	TextFont_.Draw(Stat + "%", {TextX - Space - 8, SecondY}, RGB(255, 255, 255), 20, 800);

	Stat = std::to_string((int)GameInfo::GetPlayerInfo()->MeleeRange_);
	Space = static_cast<int>(Stat.length()) * TextWidth;
	TextFont_.Draw(Stat + "%", { TextX - Space - 8, SecondY + SecondHeight }, RGB(255, 255, 255), 20, 800);

	Stat = std::to_string((int)GameInfo::GetPlayerInfo()->ShootSpeedRatio_);
	Space = static_cast<int>(Stat.length()) * TextWidth;
	TextFont_.Draw(Stat, { TextX - Space, SecondY + SecondHeight * 2 }, RGB(255, 255, 255), 20, 800);

	Stat = std::to_string((int)GameInfo::GetPlayerInfo()->Duration_);
	Space = static_cast<int>(Stat.length()) * TextWidth;
	TextFont_.Draw(Stat, { TextX - Space, SecondY + SecondHeight * 3 }, RGB(255, 255, 255), 20, 800);

	Stat = std::to_string((int)GameInfo::GetPlayerInfo()->AddShootNum_);
	Space = static_cast<int>(Stat.length()) * TextWidth;
	TextFont_.Draw(Stat, { TextX - Space, SecondY + SecondHeight * 4 }, RGB(255, 255, 255), 20, 800);

	Stat = std::to_string((int)GameInfo::GetPlayerInfo()->CoolTime_);
	Space = static_cast<int>(Stat.length()) * TextWidth;
	TextFont_.Draw(Stat + "%", { TextX - Space - 8, SecondY + SecondHeight * 5 }, RGB(255, 255, 255), 20, 800);


	float ThirdY = 429.0f;
	float ThirdHeight = 19;
	Stat = std::to_string((int)GameInfo::GetPlayerInfo()->Luck_);
	Space = static_cast<int>(Stat.length()) * TextWidth;
	TextFont_.Draw(Stat, { TextX - Space, ThirdY }, RGB(255, 255, 255), 20, 800);

	Stat = std::to_string((int)GameInfo::GetPlayerInfo()->Growth_);
	Space = static_cast<int>(Stat.length()) * TextWidth;
	TextFont_.Draw(Stat + "%", { TextX - Space - 8, ThirdY + ThirdHeight * 1 }, RGB(255, 255, 255), 20, 800);

	Stat = std::to_string((int)GameInfo::GetPlayerInfo()->Greed_);
	Space = static_cast<int>(Stat.length()) * TextWidth;
	TextFont_.Draw(Stat, { TextX - Space, ThirdY + ThirdHeight * 2 }, RGB(255, 255, 255), 20, 800);

	// 저주
	TextFont_.Draw("-", { TextX - Space, ThirdY + ThirdHeight * 3}, RGB(255, 255, 255), 20, 800);

	Stat = std::to_string((int)GameInfo::GetPlayerInfo()->Magnet_);
	Space = static_cast<int>(Stat.length()) * TextWidth;
	TextFont_.Draw(Stat, { TextX - Space, ThirdY + ThirdHeight * 4}, RGB(255, 255, 255), 20, 800);



	float FourthY = 539.0f;
	float FourthHeight = 19;
	Stat = std::to_string((int)GameInfo::GetPlayerInfo()->Revival_);
	Space = static_cast<int>(Stat.length()) * TextWidth;
	TextFont_.Draw(Stat, { TextX - Space, FourthY }, RGB(255, 255, 255), 20, 800);

	// 새로고침
	TextFont_.Draw("-", { TextX - Space, FourthY + FourthHeight * 1 }, RGB(255, 255, 255), 20, 800);
	// 건너뛰기
	TextFont_.Draw("-", { TextX - Space, FourthY + FourthHeight * 2 }, RGB(255, 255, 255), 20, 800);
	// 지우기
	TextFont_.Draw("-", { TextX - Space, FourthY + FourthHeight * 3 }, RGB(255, 255, 255), 20, 800);
}