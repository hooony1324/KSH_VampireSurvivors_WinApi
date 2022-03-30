#include "Mud.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
//#include <GameEngineBase/GameEngineDebug.h>

Mud::Mud() 
{
}

Mud::~Mud() 
{
}

void Mud::Start()
{
	CreateRenderer("Mud_0.bmp");
	SetPosition({ 800, 600 });
}

void Mud::Update()
{
}

void Mud::Render()
{
}
