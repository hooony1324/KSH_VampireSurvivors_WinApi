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

GameEngineRenderer* GameEngineActor::CreateRenderer(
	const std::string& _Image,
	RenderPivot _PivotType,
	const float4& _PivotPos)
{
	GameEngineRenderer* NewRenderer = new GameEngineRenderer();

	NewRenderer->SetActor(this);
	NewRenderer->SetImage(_Image);
	NewRenderer->SetPivot(_PivotPos);
	NewRenderer->SetType(_PivotType);

	RenderList_.push_back(NewRenderer);
	return NewRenderer;

	return nullptr;
}

void GameEngineActor::Rendering()
{
	// RenderList�� GameEngineRenderer* ��ȸ
	// ex) Player�� RenderList{����, ��ų, ĳ����, ...} ��ȸ�ϸ� �� Renderer�� Render()ȣ��
	// Actor�� Render�� Rendering()�� ������ ȣ���
	StartRenderIter = RenderList_.begin();
	EndRenderIter = RenderList_.end();

	for (; StartRenderIter != EndRenderIter; ++StartRenderIter)
	{
		(*StartRenderIter)->Render();
	}
}

