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
	SetScale(GameEngineWindow::GetScale());

	GameEngineRenderer* Map = CreateRenderer("Library_Books_x2.bmp", RenderPivot::CENTER);
	float4 MapPivot = Map->GetScale().Half();
	Map->SetPivot(MapPivot);
	
	
}

void Library::Update()
{
}

void Library::Render()
{

}
