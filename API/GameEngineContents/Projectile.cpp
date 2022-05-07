#include "Projectile.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>
#include <string>

#include "Vector2D.h"
#include "GameEnum.h"
#include "GameInfo.h"
#include "PlayLevel.h"

std::vector<std::string> ProjectileList = { "Sword.bmp", "ProjectileHoly1.bmp", "ProjectileFlameRed.bmp", "Diamond.bmp"};

Projectile::Projectile()
	: ProjImage_(nullptr)
	, ShootDir_(float4::ZERO)
	, Damage_(100)
	, Speed_(200)
	, Duration_(3)	// 지속시간
	, IsBullet_(true)
{
}

Projectile::~Projectile() 
{

}

void Projectile::Start()
{
	NextLevelOff();
	ProjImage_ = CreateRenderer("Blank.bmp", static_cast<int>(RENDER_ORDER::WEAPON));
	ProjCol_ = CreateCollision("PlayerAttack", float4{ 10, 10 });

	SetScale({ 20, 20 });
	
	MapColImage_ = PlayLevel::MapColImage_;
}

void Projectile::Update()
{
	if (Type_ == ProjectileType::DIAMOND)
	{
		// 플레이어 기준 벽 부딪히기
		// 콜맵 부딪히기
		DiamondUpdate();
	}

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

void Projectile::DiamondUpdate()
{
	//1280 640
	float4 PlayerPos = GameInfo::GetPlayerInfo()->PlayerPos_;

	// PositionCheck
	float LeftWall = PlayerPos.x - 635;
	float RightWall = PlayerPos.x + 635;
	float TopWall = PlayerPos.y - 340;
	float BotWall = PlayerPos.y + 340;

	// MapColCheck
	int ColorTop = MapColImage_->GetImagePixel(GetPosition() + float4{ 0, -20 });
	int ColorBot = MapColImage_->GetImagePixel(GetPosition() + float4{ 0, 20 });
	int ColorLeft = MapColImage_->GetImagePixel(GetPosition() + float4{ -20, 0 });
	int ColorRight = MapColImage_->GetImagePixel(GetPosition() + float4{ 20, 0 });

	if (LeftWall >= GetPosition().x || ColorLeft == RGB(0, 0, 0))
	{
		ShootDir_ = { -ShootDir_.x, ShootDir_.y };
	}

	if (RightWall <= GetPosition().x || ColorRight == RGB(0, 0, 0))
	{
		ShootDir_ = { -ShootDir_.x, ShootDir_.y };
	}

	if (TopWall >= GetPosition().y || ColorTop == RGB(0, 0, 0))
	{
		ShootDir_ = { ShootDir_.x, -ShootDir_.y };
	}

	if (BotWall <= GetPosition().y || ColorBot == RGB(0, 0, 0))
	{
		ShootDir_ = { ShootDir_.x, -ShootDir_.y };
	}

}


void Projectile::SetType(ProjectileType _BT)
{

	ProjImage_->SetImage(ProjectileList[static_cast<int>(_BT) - 1]);

	// 세부 설정
	switch (_BT)
	{
	case ProjectileType::KNIFE:
	{
		Type_ = ProjectileType::KNIFE;
		GameEngineSound::SoundPlayOneShot("ProjectileKnife.mp3", 0);
		ProjImage_->SetRotationFilter("Sword_Filter.bmp");
		break;
	}
	case ProjectileType::FLAME_BLUE:
	{
		Type_ = ProjectileType::FLAME_BLUE;
		GameEngineSound::SoundPlayOneShot("ProjectileMagic.mp3", 0);
		ProjImage_->SetRotationFilter("ProjectileHoly1_Filter.bmp");
		break;
	}
	case ProjectileType::FLAME_RED:
		Type_ = ProjectileType::FLAME_RED;
		GameEngineSound::SoundPlayOneShot("ProjectileMagic.mp3", 0);
		ProjImage_->SetRotationFilter("ProjectileFlameRed_Filter.bmp");
		break;

	case ProjectileType::DIAMOND:
		Type_ = ProjectileType::DIAMOND;
		GameEngineSound::SoundPlayOneShot("ProjectileMagic.mp3", 0);
		ProjImage_->SetRotationFilter("Diamond_Filter.bmp");
		IsBullet_ = false;
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
