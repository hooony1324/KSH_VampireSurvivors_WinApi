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
	SetPosition({ 0, 0 });
	SetScale({ 1280, 800 });
}

void Library::Update()
{
}

void Library::Render()
{
	DebugRectRender();
}
