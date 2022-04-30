#include "WeaponSlots.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>

#include "GameInfo.h"

WeaponSlots::WeaponSlots() 
	:ActiveCount_(1),
	PassiveCount_(0)
{
}

WeaponSlots::~WeaponSlots() 
{
}

void WeaponSlots::Start()
{
	GameEngineRenderer* Slot = CreateRenderer("WeaponSlots.bmp", static_cast<int>(RENDER_ORDER::PLAY_UI));
	
	SetPosition(float4{ 4, 32 });
	SetScale(Slot->GetScale());
	Slot->SetPivot(Slot->GetScale().Half());
	Slot->CameraEffectOff();
	Slot->SetTransColor(RGB(0, 0, 0));
	Slot->SetAlpha(100);

	// Ω∫≈≥ ΩΩ∏© √ ±‚»≠
	for (int i = 0; i < 6; i++)
	{
		GameEngineRenderer* ActiveSkillPtr = CreateRenderer("KnifeUISmall.bmp", static_cast<int>(RENDER_ORDER::PLAY_UI));
		GameEngineRenderer* PassiveSkillPtr = CreateRenderer("KnifeUISmall.bmp", static_cast<int>(RENDER_ORDER::PLAY_UI));

		ActiveSkillPtr->CameraEffectOff();
		ActiveSkillPtr->SetPivot(float4{ 13, 12 } + float4{ (static_cast<float>(i) * 27) + (static_cast<float>(i) * 1), 0 });
		ActiveSkillPtr->Off();

		PassiveSkillPtr->CameraEffectOff();
		PassiveSkillPtr->SetPivot(float4{ 13, 40 } + float4{ (static_cast<float>(i) * 27) + (static_cast<float>(i) * 1), 0 });
		PassiveSkillPtr->Off();

		ActiveSlots_.push_back(ActiveSkillPtr);
		PassiveSlots_.push_back(PassiveSkillPtr);
	}

	// 1π¯ ΩΩ∏© 
	ActiveSlots_[0]->On();
	SkillType Type = GameInfo::GetPlayerInfo()->ActiveSkillSlot_[0];
	ActiveSlots_[0]->SetImage(SkillTypeToName(Type) + "UISmall.bmp");


	NextLevelOff();
}

void WeaponSlots::Update()
{
	SkillCheck();
}

void WeaponSlots::Render()
{
}

void WeaponSlots::SkillCheck()
{

	for (size_t i = 0; i < GameInfo::GetPlayerInfo()->ActiveSkillSlot_.size(); i++)
	{
		SkillType Type = GameInfo::GetPlayerInfo()->ActiveSkillSlot_[i];
		if (1 > GameInfo::GetPlayerInfo()->AllSkillLevel_[Type])
		{
			continue;
		}
		ActiveSlots_[i]->On();
		ActiveSlots_[i]->SetImage(SkillTypeToName(Type) + "UISmall.bmp");

	}

	for (size_t i = 0; i < GameInfo::GetPlayerInfo()->PassiveSkillSlot_.size(); i++)
	{
		SkillType Type = GameInfo::GetPlayerInfo()->PassiveSkillSlot_[i];
		if (1 > GameInfo::GetPlayerInfo()->AllSkillLevel_[Type])
		{
			continue;
		}
		PassiveSlots_[i]->On();
		PassiveSlots_[i]->SetImage(SkillTypeToName(Type) + "UISmall.bmp");
	}

}
