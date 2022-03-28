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
	, ImageName_("old.bmp")
{
}

Character::~Character() 
{
}

void Character::SetDefault()
{
	ImageName_ = "Old.bmp";
	Name_ = "Old";

	Speed_		= 200.0f;
	Hp_			= 100;
	Recovery_	= 0;
	Guard_		= 0;
	Power_		= 0;
	Range_		= 1;
	ShootSpeed_ = 1;
	ShootNum_	= 1;
	Duration_	= 3;
	Luck_		= 0;
	Growth_		= 1;
	Greed_		= 1;
	Magnet_		= 1;
	Revival_	= 0;
}

void Character::SetOld()
{
	ImageName_ = "Old.bmp";
	Name_ = "Old";

	Speed_		= 150.0f;
	Hp_			= 100;
	Recovery_	= 0;
	Guard_		= 0;
	Power_		= 0;
	Range_		= 1;
	ShootSpeed_	= 1;
	ShootNum_	= 1;
	Duration_	= 3;
	Luck_		= 0;
	Growth_		= 1;
	Greed_		= 1;
	Magnet_		= 1;
	Revival_	= 0;
}

void Character::SetCavallo()
{
	ImageName_ = "Cavallo.bmp";
	Name_ = "Cavallo";

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

void Character::SetImelda()
{
	ImageName_ = "Imelda.bmp";
	Name_ = "Imelda";

	Speed_		= 200.0f;
	Hp_			= 100;
	Recovery_	= 0;
	Guard_		= 0;
	Power_		= 0;
	Range_		= 1;
	ShootSpeed_ = 1;
	ShootNum_	= 1;
	Duration_	= 3;
	Luck_		= 0;
	Growth_		= 1;
	Greed_		= 1;
	Magnet_		= 1;
	Revival_	= 0;
}



