#include "Library.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>

Library::Library() 
{
}

Library::~Library() 
{
}

void Library::Start()
{
	SetPosition({ 0, 0 });

	// Library_Books_x2 : 3686 x 1844
	GameEngineRenderer* Map = CreateRenderer("Library_BaseLoop_x2.bmp", RenderPivot::CENTER);
	float4 MapPivot = Map->GetScale().Half();
	Map->SetPivot(MapPivot);
	
	SetScale(Map->GetScale());
	
}

void Library::Update()
{
	
}

void Library::Render()
{

}
