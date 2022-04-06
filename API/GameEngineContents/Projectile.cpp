#include "Projectile.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
//#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngine/GameEngineCollision.h>

#include "PlayerInfo.h"
#include "Vector2D.h"


Projectile::Projectile() 
{
}

Projectile::~Projectile() 
{
}

void Projectile::Start()
{

	CreateRenderer("sword.bmp");
	ShootDir_ = float4::RIGHT; // �ܺο��� �������� ������ ����


}

void Projectile::Update()
{
	SetMove(ShootDir_);
}
