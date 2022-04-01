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
	// Library_Books_x2
	// - Pos   { 0, 0 }
	// - Scale 3686 x 1844
	Map_ = CreateRenderer("Library_BaseLoop_x2.bmp", RenderPivot::CENTER);
	SetPosition({ 0, 0 });
	SetScale(Map_->GetScale());
	Map_->SetPivot(Map_->GetScale().Half());
	
	
}

void Library::Update()
{
	
}

void Library::Render()
{

}
