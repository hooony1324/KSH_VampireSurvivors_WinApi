#include "GameEngineRenderer.h"
#include "GameEngineImageManager.h"
#include "GameEngine.h"
#include <GameEngineBase/GameEngineDebug.h>

#pragma comment(lib, "msimg32.lib")

GameEngineRenderer::GameEngineRenderer() 
	: Image_(nullptr)
	, PivotType_(RenderPivot::CENTER)
	, ScaleMode_(RenderScaleMode::Image)
	, TransColor_(RGB(255, 0, 255)) // Magenta색 투명처리
{
}

GameEngineRenderer::~GameEngineRenderer() 
{
}

void GameEngineRenderer::SetImage(const std::string& _Name)
{
	GameEngineImage* FindImage = GameEngineImageManager::GetInst()->Find(_Name);
	if (nullptr == FindImage)
	{
		MsgBoxAssertString(_Name + "존재하지 않는 이미지를 랜더러에 세팅하려고 했습니다");
		return;
	}

	Image_ = FindImage;
}

void GameEngineRenderer::Render()
{
	if (nullptr == Image_)
	{
		MsgBoxAssert("렌더러에 이미지가 세팅되어 있지 않아 랜더링 실패하였습니다");
		return;
	}

	float4 RenderPos = GetActor()->GetPosition() + RenderPivot_;

	float4 RenderScale = RenderScale_;

	switch (ScaleMode_)
	{
	case RenderScaleMode::Image:
		RenderScale = Image_->GetScale();
		break;
	case RenderScaleMode::User:
		break;
	default:
		break;
	}

	switch (PivotType_)
	{
	case RenderPivot::CENTER:
		GameEngine::BackBufferImage()->TransCopyCenterScale(Image_, RenderPos, RenderScale, TransColor_);
		break;
	case RenderPivot::BOT:
		// GameEngine::BackBufferImage()->TransCopyCenterScale(Image_, RenderPos, RenderScale, TransColor_);
		break;
	default:
		break;
	}
}

