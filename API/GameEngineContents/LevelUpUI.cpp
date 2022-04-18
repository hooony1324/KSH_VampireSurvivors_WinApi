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
	// 배경 
	GameEngineRenderer* Renderer = CreateRenderer("LevelUpUI.bmp");
	SetScale(Renderer->GetScale());
	Renderer->CameraEffectOff();
	Renderer->SetPivot(GameEngineWindow::GetScale().Half() + float4{0, 10});

	// 사운드
	GameEngineSound::SoundPlayOneShot("LevelUp.MP3", 0);
	GameInfo::SetPause(true);
	IsActivated_ = true;

	int SelectNum = 3;
	// 무기 선택 박스 1
	Renderer1_ = CreateRenderer();
	Renderer1_->SetImage("LevelUpMagicwand.bmp");
	Renderer1_->CameraEffectOff();
	Renderer1_->SetPivot(GameEngineWindow::GetScale().Half() + float4{2, -Renderer1_->GetImageScale().y});

	// 무기 선택 박스 2
	Renderer2_ = CreateRenderer();
	Renderer2_->SetImage("LevelUpMagicwand.bmp");
	Renderer2_->CameraEffectOff();
	Renderer2_->SetPivot(GameEngineWindow::GetScale().Half() + float4{ 2, 0 });

	// 무기 선택 박스 3
	Renderer3_ = CreateRenderer();
	Renderer3_->SetImage("LevelUpMagicwand.bmp");
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
		Renderer4_->SetImage("LevelUpMagicwand.bmp");
		Renderer4_->CameraEffectOff();
		Renderer4_->SetPivot(GameEngineWindow::GetScale().Half() + float4{ 2, Renderer1_->GetImageScale().y * 2 });

		SelectNum = 4;
	}

	// 중요 : 처음엔 0 ~ 10 이지만 나중에는 뽑은 스킬의 상태에 따라 뽑을 수 있는 스킬배열이 달라져야 함 ex. SelectableSkills[]
	// 0 ~ 10 연속으로 SelectNum개의 겹치지 않는 랜덤수 뽑기
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


	// 아이템 선택
	if (true == GameEngineInput::GetInst()->IsDown("Num1"))
	{
		// 플레이어에게 무기 장착
		


		// 종료
		Death();
		CreateCount_--;
		GameInfo::SetPause(false);
		IsActivated_ = false;
	}


}

void LevelUpUI::Render()
{
}
