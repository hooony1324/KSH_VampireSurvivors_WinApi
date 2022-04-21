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
	SetPosition(float4{8, 40});
	GameEngineRenderer* RendererBack = CreateRenderer("StatUI.bmp");
	GameEngineRenderer* RendererText = CreateRenderer("StatUIText.bmp");


	SetScale(RendererBack->GetScale());
	RendererBack->SetAlpha(100);
	RendererBack->CameraEffectOff();
	RendererBack->SetPivot(RendererBack->GetScale().Half());

	RendererText->CameraEffectOff();
	RendererText->SetPivot(RendererText->GetScale().Half());

	SetSlotBase();

	// 처음에 주어진 스킬은 활성화
	{
		ActiveSlots_[0]->On();
		ActiveSkills_[0]->On();
		ActiveLevels_[0]->On();

		SkillType SkillName = GameInfo::GetPlayerInfo()->ActiveSkillSlot_[0];
	}

}

void StatUI::Update()
{
	SlotUpdate();
}

void StatUI::Render()
{
}

void StatUI::SlotUpdate()
{
	// 액티브
	std::vector<SkillType> ActiveSkillSlot = GameInfo::GetPlayerInfo()->ActiveSkillSlot_;
	if (ActiveSkillCount_ != ActiveSkillSlot.size())
	{
		ActiveSkillCount_ = ActiveSkillSlot.size();
		ActiveSlots_[ActiveSkillCount_ - 1]->On();
		ActiveSkills_[ActiveSkillCount_ - 1]->On();
		ActiveLevels_[ActiveSkillCount_ - 1]->On();

		int SkillType = static_cast<int>(ActiveSkillSlot[ActiveSkillCount_ - 1]);
		ActiveSkills_[ActiveSkillCount_ - 1]->SetImage(SkillOrder[SkillType] + "UI.bmp");
	}

	// 엑티브 레벨
	for (int i = 0; i < static_cast<int>(ActiveSkillSlot.size()); i++)
	{
		SkillType Skill = ActiveSkillSlot[i];
		int SkillLevel = GameInfo::GetPlayerInfo()->SkillLevelInfo_[static_cast<int>(Skill)];
		ActiveLevels_[i]->SetImage("WeaponLevel_" + std::to_string(SkillLevel) + ".bmp");
	}

	// 패시브
	std::vector<SkillType> PassiveSkillSlot = GameInfo::GetPlayerInfo()->PassiveSkillSlot_;
	if (PassiveSkillCount_ != PassiveSkillSlot.size())
	{
		PassiveSkillCount_ = PassiveSkillSlot.size();
		PassiveSlots_[PassiveSkillCount_ - 1]->On();
		PassiveSkills_[PassiveSkillCount_ - 1]->On();
		PassiveLevels_[PassiveSkillCount_ - 1]->On();

		int SkillType = static_cast<int>(PassiveSkillSlot[PassiveSkillCount_ - 1]);
		PassiveSkills_[PassiveSkillCount_ - 1]->SetImage(SkillOrder[SkillType] + "UI.bmp");
	}

	// 패시브 레벨
	for (int i = 0; i < static_cast<int>(PassiveSkillSlot.size()); i++)
	{
		SkillType Skill = PassiveSkillSlot[i];
		int SkillLevel = GameInfo::GetPlayerInfo()->SkillLevelInfo_[static_cast<int>(Skill)];
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
}
