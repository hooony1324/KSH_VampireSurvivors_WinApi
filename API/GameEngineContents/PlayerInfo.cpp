#include "PlayerInfo.h"

#include "Character.h"

PlayerInfo* PlayerInfo::Inst_ = new PlayerInfo();

void PlayerInfo::ChangeCharacter(Character::Type _Type)
{
	switch (_Type)
	{
	case Character::Type::Old:
		Character_->SetCharacter(Character::Type::Old);
		break;
	case Character::Type::Cavallo:
		Character_->SetCharacter(Character::Type::Cavallo);
		break;
	case Character::Type::Imelda:
		Character_->SetCharacter(Character::Type::Imelda);
		break;

		// ...

	default:
		Character_->SetCharacter(Character::Type::Cavallo);
		break;
	}
		

}

PlayerInfo::PlayerInfo()
	: SurvivalTime_(0)
	, EearnedGold_(0)
	, CharacterLevel_(0)
	, KillCount_(0)
	, Character_(new Character())
	, CurrentExp_(0)
	, MaxExp_(0)
	, PlayerLevel_(0)

{
	MaxExp_ = 100;
}

PlayerInfo::~PlayerInfo() 
{
	if (nullptr != Character_)
	{
		delete Character_;
		Character_ = nullptr;
	}
}

