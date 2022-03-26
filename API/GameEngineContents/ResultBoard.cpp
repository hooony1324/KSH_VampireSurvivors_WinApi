#include "ResultBoard.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineDebug.h>

ResultBoard::ResultBoard() 
{
}

ResultBoard::~ResultBoard() 
{
}

void ResultBoard::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale({ 700, 700 });


}

void ResultBoard::Update()
{
}

void ResultBoard::Render()
{

}
