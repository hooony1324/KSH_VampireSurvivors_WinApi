#include "Projectile.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
//#include <GameEngineBase/GameEngineDebug.h>

Projectile::Projectile() 
{
	CreateRenderer("sword.bmp");
}

Projectile::~Projectile() 
{
}

void Projectile::Start()
{
	ShootDir_ = float4::RIGHT;
}

void Projectile::Update()
{
	// ���͸� ���� �߻��ϴ� ��� �߰��ؾߵ�
	SetMove(ShootDir_ *GameEngineTime::GetDeltaTime() * 200.0f);
}
