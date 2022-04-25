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
	/*SetPosition(Slot->GetScale().Half() + float4{ 0, 35 });
	SetScale(Slot->GetScale());*/
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
	int SkillType = static_cast<int>(GameInfo::GetPlayerInfo()->ActiveSkillSlot_[0]);
	ActiveSlots_[0]->SetImage(SkillOrder[SkillType] + "UISmall.bmp");


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
	size_t ActiveSize = GameInfo::GetPlayerInfo()->ActiveSkillSlot_.size();

	if (ActiveSize != ActiveCount_)
	{
		ActiveCount_ = ActiveSize;
		ActiveSlots_[ActiveCount_ - 1]->On();
		int SkillType = static_cast<int>(GameInfo::GetPlayerInfo()->ActiveSkillSlot_[ActiveCount_ - 1]);
		ActiveSlots_[ActiveCount_ - 1]->SetImage(SkillOrder[SkillType] + "UISmall.bmp");
	}

	size_t PassiveSize = GameInfo::GetPlayerInfo()->PassiveSkillSlot_.size();

	if (PassiveSize != PassiveCount_)
	{
		PassiveCount_ = PassiveSize;
		PassiveSlots_[PassiveCount_ - 1]->On();
		int SkillType = static_cast<int>(GameInfo::GetPlayerInfo()->PassiveSkillSlot_[PassiveCount_ - 1]);
		PassiveSlots_[PassiveCount_ - 1]->SetImage(SkillOrder[SkillType] + "UISmall.bmp");
	}

}
