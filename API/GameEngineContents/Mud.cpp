#include "Mud.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
//#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngine/GameEngineRenderer.h>

Mud::Mud() 
{
}

Mud::~Mud() 
{
}

void Mud::Start()
{
	Mud_ = CreateRenderer("Mud_0.bmp");
	SetPosition({ 800, 600 });

	GameEngineUpdateObject::On();
}

void Mud::Update()
{
	// �÷��̾� ��ġ ����

}

void Mud::Render()
{
}
