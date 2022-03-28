#include "PlayerInfo.h"

#include "Character.h"

PlayerInfo* PlayerInfo::Inst_ = new PlayerInfo();

void PlayerInfo::ChangeCharacter(Character::Type _Type)
{
	switch (_Type)
	{
	case Character::Type::Old:
		Character_->SetOld();
		break;
	case Character::Type::Cavallo:
		Character_->SetCavallo();
		break;
	case Character::Type::Imelda:
		Character_->SetImelda();
		break;

		// ...

	default:
		Character_->SetDefault();
		break;
	}
		

}

PlayerInfo::PlayerInfo()
	: SurvivalTime_(0)
	, EearnedGold_(0)
	, CharacterLevel_(0)
	, KillCount_(0)
	, Character_(new Character())

{
	
}

PlayerInfo::~PlayerInfo() 
{
}

