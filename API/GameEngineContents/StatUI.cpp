#include "StatUI.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>

#include "GameInfo.h"
#include <string>


StatUI::StatUI()
	: ActiveSlotIndex_(0)
	, ActivatedSkill_(SkillType::NONE)
	
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

	ActivatedSkill_ = GameInfo::GetPlayerInfo()->ActiveSkillSlot_[0];
}

void StatUI::Update()
{
	

	std::vector<SkillType> ActiveSkillSlot = GameInfo::GetPlayerInfo()->ActiveSkillSlot_;

	
	
	for (int i = 0; i < static_cast<int>(ActiveSkillSlot.size()); i++)
	{
		SkillType NewSkill = ActiveSkillSlot[i];

		// 레벨은 상시 확인
		int SkillLevel = GameInfo::GetPlayerInfo()->SkillLevelInfo_[static_cast<int>(NewSkill)];
		ActiveLevels_[i]->On();
		ActiveLevels_[i]->SetImage("WeaponLevel_" + std::to_string(SkillLevel) + ".bmp");

		if (SkillLevel >= 2)
		{
			int a = 0;
		}
		
		ActivatedSkill_ = NewSkill;

		ActiveSlots_[i]->On();
		
		std::string SkillName = SkillOrder[static_cast<int>(ActivatedSkill_)];
		ActiveSkills_[i]->On();
		ActiveSkills_[i]->SetImage(SkillName + "UI.bmp");

	}
	
}

void StatUI::Render()
{
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
