#include "Character.h"

Character::Character() 
	: Speed_(0)
	, CurrentHp_(0)
	, MaxHp_(0)
	, Recovery_(0)
	, Guard_(0)
	, Power_(0)
	, MeleeRange_(0)
	, ShootSpeedRatio_(0)
	, AddShootNum_(0)
	, Duration_(0)
	, Luck_(0)
	, Growth_(0)
	, Greed_(0)
	, Magnet_(0)
	, Revival_(0)
	, ImageName_()
{
}

Character::Character(CharacterType _CharacterType)
{
	SetCharacter(_CharacterType);
}

Character::~Character() 
{

}


void Character::SetCharacter(CharacterType _CharacterType)
{
	switch (_CharacterType)
	{

	case CharacterType::Imelda:
	{
		ImageName_ = "Imelda.bmp";
		Name_ = "Imelda";
		WalkRightAnim_ = "Imelda_WalkRight.bmp";
		WalkLeftAnim_ = "Imelda_WalkLeft.bmp";

		Speed_ = 200.0f;
		MaxHp_ = 100;
		CurrentHp_ = MaxHp_;
		Recovery_ = 0;
		Guard_ = 0;
		Power_ = 0;
		MeleeRange_ = 1;
		ShootSpeedRatio_ = 1;
		Duration_ = 3;
		AddShootNum_ = 1;
		CoolTime_ = 0;
		Luck_ = 20;
		Growth_ = 1;
		Greed_ = 1;
		Magnet_ = 1;
		Revival_ = 0;

		BaseSkill_ = SkillType::MAGICWAND;
		break;
	}

	case CharacterType::Cavallo:
	{
		ImageName_ = "Cavallo.bmp";
		Name_ = "Cavallo";
		WalkRightAnim_ = "Cavallo_WalkRight.bmp";
		WalkLeftAnim_ = "Cavallo_WalkLeft.bmp";

		Speed_ = 200.0f;
		MaxHp_ = 100;
		CurrentHp_ = MaxHp_;
		Recovery_ = 0;
		Guard_ = 0;
		Power_ = 0;
		MeleeRange_ = 1;
		ShootSpeedRatio_ = 1;
		Duration_ = 3;
		AddShootNum_ = 1;
		CoolTime_ = 0;
		Luck_ = 0;
		Growth_ = 1;
		Greed_ = 1;
		Magnet_ = 1;
		Revival_ = 0;

		BaseSkill_ = SkillType::KNIFE;
		break;
	}

	case CharacterType::Old:
	{
		ImageName_ = "Poe.bmp";
		Name_ = "Poe";
		WalkRightAnim_ = "Poe_WalkRight.bmp";
		WalkLeftAnim_ = "Poe_WalkLeft.bmp";

		Speed_ = 150.0f;
		MaxHp_ = 100;
		CurrentHp_ = MaxHp_;
		Recovery_ = 0;
		Guard_ = 0;
		Power_ = 0;
		MeleeRange_ = 1;
		ShootSpeedRatio_ = 1;
		Duration_ = 3;
		AddShootNum_ = 1;
		CoolTime_ = 0;
		Luck_ = 0;
		Growth_ = 1;
		Greed_ = 1;
		Magnet_ = 1;
		Revival_ = 0;

		BaseSkill_ = SkillType::FIREWAND;
		break;
	}

	default:
	{
		ImageName_ = "Cavallo.bmp";
		Name_ = "Cavallo";
		WalkRightAnim_ = "Cavallo_WalkRight.bmp";
		WalkLeftAnim_ = "Cavallo_WalkLeft.bmp";

		Speed_ = 200.0f;
		MaxHp_ = 100;
		CurrentHp_ = MaxHp_;
		Recovery_ = 0;
		Guard_ = 0;
		Power_ = 0;
		MeleeRange_ = 1;
		ShootSpeedRatio_ = 1;
		Duration_ = 3;
		AddShootNum_ = 1;
		CoolTime_ = 0;
		Luck_ = 0;
		Growth_ = 1;
		Greed_ = 1;
		Magnet_ = 1;
		Revival_ = 0;

		BaseSkill_ = SkillType::KNIFE;
		break;
	}

	}
}


