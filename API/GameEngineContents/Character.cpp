#include "Character.h"

Character::Character() 
	: Speed_(0)
	, Hp_(0)
	, Recovery_(0)
	, Guard_(0)
	, Power_(0)
	, Range_(0)
	, ShootSpeed_(0)
	, ShootNum_(0)
	, Duration_(0)
	, Luck_(0)
	, Growth_(0)
	, Greed_(0)
	, Magnet_(0)
	, Revival_(0)
	, ImageName_("Cavallo.bmp")
{
}

Character::~Character() 
{
}

void Character::SetCharacter(Type _CharacterType)
{
	switch (_CharacterType)
	{
	case Type::Cavallo:
	{
		ImageName_ = "Cavallo.bmp";
		Name_ = "Cavallo";
		WalkRightAnim_ = "Cavallo_WalkRight.bmp";
		WalkLeftAnim_ = "Cavallo_WalkLeft.bmp";

		Speed_ = 200.0f;
		Hp_ = 100;
		Recovery_ = 0;
		Guard_ = 0;
		Power_ = 0;
		Range_ = 1;
		ShootSpeed_ = 1;
		ShootNum_ = 1;
		Duration_ = 3;
		Luck_ = 0;
		Growth_ = 1;
		Greed_ = 1;
		Magnet_ = 1;
		Revival_ = 0;
	}
		break;

	case Type::Imelda:
	{
		ImageName_ = "Imelda.bmp";
		Name_ = "Imelda";
		WalkRightAnim_ = "Imelda_WalkRight.bmp";
		WalkLeftAnim_ = "Imelda_WalkLeft.bmp";

		Speed_ = 200.0f;
		Hp_ = 100;
		Recovery_ = 0;
		Guard_ = 0;
		Power_ = 0;
		Range_ = 1;
		ShootSpeed_ = 1;
		ShootNum_ = 1;
		Duration_ = 3;
		Luck_ = 0;
		Growth_ = 1;
		Greed_ = 1;
		Magnet_ = 1;
		Revival_ = 0;
	}
		break;

	case Type::Old:
	{
		ImageName_ = "Old.bmp";
		Name_ = "Old";
		WalkRightAnim_ = "Old_WalkRight.bmp";
		WalkLeftAnim_ = "Old_WalkLeft.bmp";

		Speed_ = 150.0f;
		Hp_ = 100;
		Recovery_ = 0;
		Guard_ = 0;
		Power_ = 0;
		Range_ = 1;
		ShootSpeed_ = 1;
		ShootNum_ = 1;
		Duration_ = 3;
		Luck_ = 0;
		Growth_ = 1;
		Greed_ = 1;
		Magnet_ = 1;
		Revival_ = 0;
	}
		break;

	default:
	{
		ImageName_ = "Cavallo.bmp";
		Name_ = "Cavallo";
		WalkRightAnim_ = "Cavallo_WalkRight.bmp";
		WalkLeftAnim_ = "Cavallo_WalkLeft.bmp";

		Speed_ = 200.0f;
		Hp_ = 100;
		Recovery_ = 0;
		Guard_ = 0;
		Power_ = 0;
		Range_ = 1;
		ShootSpeed_ = 1;
		ShootNum_ = 1;
		Duration_ = 3;
		Luck_ = 0;
		Growth_ = 1;
		Greed_ = 1;
		Magnet_ = 1;
		Revival_ = 0;
	}
		break;
	}
}


