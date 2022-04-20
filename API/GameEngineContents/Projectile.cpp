#include "Projectile.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
//#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>
#include <string>

#include "Vector2D.h"
#include "GameEnum.h"

std::vector<std::string> ProjectileList = { "Sword.bmp", "ProjectileHoly1.bmp", "ProjectileFlameRed.bmp" };

Projectile::Projectile()
	: ProjImage_(nullptr)
	, ShootDir_(float4::ZERO)
	, Damage_(10)
	, Speed_(200)
	, Duration_(3)	// 지속시간
{
}

Projectile::~Projectile() 
{

}

void Projectile::Start()
{
	ProjImage_ = CreateRenderer("Blank.bmp");
	ProjCol_ = CreateCollision("PlayerAttack", float4{ 10, 10 });

	SetScale({ 20, 20 });
	ShootDir_ = float4::RIGHT;
	Damage_ = 10;
	NextLevelOff();
	
}

void Projectile::Update()
{
	float DeltaTime = GameEngineTime::GetDeltaTime(static_cast<int>(TIME_GROUP::WEAPON));
	SetMove(ShootDir_ * DeltaTime * Speed_);
	Duration_ -= DeltaTime;


	if (0.05f > Duration_)
	{
		Death();
	}
}

void Projectile::Render()
{
}


void Projectile::SetType(BulletType _BT)
{

	ProjImage_->SetImage(ProjectileList[static_cast<int>(_BT)]);

	// 세부 설정
	switch (_BT)
	{
	case BulletType::KNIFE:
	{
		GameEngineSound::SoundPlayOneShot("ProjectileKnife.mp3", 0);

		ProjImage_->SetRotationFilter("Sword_Filter.bmp");
		ProjCol_->SetPivot(ShootDir_ * 18);
		Speed_ = 550.0f;
		break;
	}
	case BulletType::FLAME_BLUE:
	{
		GameEngineSound::SoundPlayOneShot("ProjectileMagic.mp3", 0);

		ProjImage_->SetRotationFilter("ProjectileHoly1_Filter.bmp");
		ProjCol_->SetPivot(ShootDir_ * 10);
		Speed_ = 500.0f;
		break;
	}
	case BulletType::FLAME_RED:
		
		GameEngineSound::SoundPlayOneShot("ProjectileMagic.mp3", 0);
		
		ProjImage_->SetRotationFilter("ProjectileFlameRed_Filter.bmp");
		ProjCol_->SetPivot(ShootDir_ * 10);
		Speed_ = 300.0f;
		break;

	}

}

void Projectile::SetDir(float4 _Direction)
{
	ShootDir_ = _Direction;

	// Degree == 180일때 문제
	float Degree = Vector2D::NormalizedDirToDegree(ShootDir_);
	ProjImage_->SetRotationZ(Degree);
}
