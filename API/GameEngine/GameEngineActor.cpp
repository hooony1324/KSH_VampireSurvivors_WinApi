#include "GameEngineActor.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineRenderer.h>


GameEngineActor::GameEngineActor() 
	: Level_(nullptr)
{
}

GameEngineActor::~GameEngineActor() 
{
	std::list<GameEngineRenderer*>::iterator StartIter = RenderList_.begin();
	std::list<GameEngineRenderer*>::iterator EndIter = RenderList_.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (nullptr == (*StartIter))
		{
			continue;
		}
		delete (*StartIter);
		(*StartIter) = nullptr;
	}
}

void GameEngineActor::DebugRectRender()
{
	GameEngineRect DebugRect(Position_, Scale_);

	Rectangle(
		GameEngine::BackBufferDC(),
		DebugRect.CenterLeft(),
		DebugRect.CenterTop(),
		DebugRect.CenterRight(),
		DebugRect.CenterBot()
	);
}

GameEngineRenderer* GameEngineActor::CreateRenderer(RenderPivot _PivotType /*= RenderPivot::CENTER*/, const float4& _PivotPos /*= {0, 0}*/)
{
	GameEngineRenderer* NewRenderer = new GameEngineRenderer();

	NewRenderer->SetActor(this);
	NewRenderer->SetPivot(_PivotPos);
	NewRenderer->SetPivotType(_PivotType);

	RenderList_.push_back(NewRenderer);
	return NewRenderer;
}

GameEngineRenderer* GameEngineActor::CreateRenderer(
	const std::string& _Image,
	RenderPivot _PivotType,
	const float4& _PivotPos)
{
	GameEngineRenderer* NewRenderer = new GameEngineRenderer();

	NewRenderer->SetActor(this);
	NewRenderer->SetImage(_Image);
	NewRenderer->SetPivot(_PivotPos);
	NewRenderer->SetPivotType(_PivotType);

	RenderList_.push_back(NewRenderer);
	return NewRenderer;
}

GameEngineRenderer* GameEngineActor::CreateRendererToScale(const std::string& _Image, const float4& _Scale, RenderPivot _PivotType, const float4& _PivotPos)
{
	GameEngineRenderer* NewRenderer = new GameEngineRenderer();

	NewRenderer->SetActor(this);
	NewRenderer->SetImage(_Image);
	NewRenderer->SetScale(_Scale);
	NewRenderer->SetPivot(_PivotPos);
	NewRenderer->SetPivotType(_PivotType);

	RenderList_.push_back(NewRenderer);
	return NewRenderer;
}

void GameEngineActor::Renderering()
{
	// RenderList의 GameEngineRenderer* 순회
	// ex) Player의 RenderList{무기, 스킬, 캐릭터, ...} 순회하며 각 Renderer의 Render()호출
	// Actor의 Render는 Rendering()이 끝나고 호출됨
	StartRenderIter = RenderList_.begin();
	EndRenderIter = RenderList_.end();

	for (; StartRenderIter != EndRenderIter; ++StartRenderIter)
	{
		(*StartRenderIter)->Render();
	}
}

