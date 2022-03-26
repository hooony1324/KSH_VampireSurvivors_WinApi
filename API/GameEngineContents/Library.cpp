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

	CreateRenderer("LibraryTile.bmp");
}

void Library::Update()
{
}

void Library::Render()
{

}
