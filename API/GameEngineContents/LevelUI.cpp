#include "LevelUI.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
//#include <GameEngineBase/GameEngineDebug.h>

#include "ObjectEnum.h"
#include <GameEngine/GameEngineRenderer.h>
#include "GameInfo.h"

LevelUI::LevelUI() 
{
}

LevelUI::~LevelUI() 
{
}

void LevelUI::Start()
{
	SetPosition({ GameEngineWindow::GetScale().x - 40, 15 });
	SetScale({ 40, 40 });


	Number1_ = CreateRenderer();
	Number1_->CameraEffectOff();
	Number2_ = CreateRenderer();
	Number2_->CameraEffectOff();
	Number3_ = CreateRenderer();
	Number3_->CameraEffectOff();

	Number1_->SetPivot(float4{ -10, 0 });
	Number2_->SetPivot(float4{ 5, 0 });
	Number3_->SetPivot(float4{ 20, 0 });

	Number1_->SetImage("1.bmp");
	Number1_->SetScale(float4{20, 30});
	Number2_->SetImage("2.bmp");
	Number2_->SetScale(float4{ 20, 30 });
	Number3_->SetImage("3.bmp");
	Number3_->SetScale(float4{ 20, 30 });

}

void LevelUI::Update()
{
	int PlayerLevel = GameInfo::GetPlayerInfo()->Level_;
}

void LevelUI::Render()
{
}
