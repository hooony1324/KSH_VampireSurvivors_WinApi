#include "Library.h"
#include <GameEngineBase/GameEngineWindow.h>

Library::Library() 
{
}

Library::~Library() 
{
}

void Library::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale(GameEngineWindow::GetScale());
}

void Library::Update()
{
}

void Library::Render()
{
	DebugRectRender();
}
