#include "ExpGem.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
//#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>


float ExpGem::RedExp_ = 100.0f; // ·£´ý°æÇèÄ¡

ExpGem::ExpGem()
{
}

ExpGem::~ExpGem()
{
}

void ExpGem::SetType(GemType _Type)
{
	switch (_Type)
	{
		case GemType::GREEN:
		{
			Renderer_->SetImage("GemGreen.bmp");
			Exp_ = 130.0f;
			break;
		}

		case GemType::BLUE:
		{
			Renderer_->SetImage("GemBlue.bmp");
			Exp_ = 20.0f;
			break;
		}

		case GemType::RED:
		{
			Renderer_->SetImage("GemBlue.bmp");
			Exp_ = RedExp_;
			break;
		}
	}
}

void ExpGem::Start()
{
	Renderer_ = CreateRenderer("GemGreen.bmp");
	Col_ = CreateCollision("ExpGem", Renderer_->GetScale());
	
}

void ExpGem::Update()
{

}