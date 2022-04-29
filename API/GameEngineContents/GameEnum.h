#pragma once

enum class ACTOR_ORDER
{
	BACKGROUND,
	PLAYER,
	ITEM,
	MONSTER,
	UI
};

enum class RENDER_ORDER
{
	BACKGROUND,
	MONSTER,
	PLAYER,
	WEAPON,
	ITEM,
	PLAY_UI,
	UI,
	UI2,
};

enum class TIME_GROUP
{
	NONE,
	PLAYER,
	MONSTER,
	WEAPON,
	TIMER,
	ITEM
};


const int SKILL_LEVELMAX = 8;
const int ACTIVE_MAX = 3;
enum class SkillType
{
	// @@@ Attribute : Active @@@

	// ����
	KNIFE,
	MAGICWAND,
	FIREWAND,
	//RUNETRACER,
	//AXE,
	//CLOCKLANCET,
	//CROSS,

	// ������
	//KINGBIBLE,
	//WHIP,
	//GARLIC,
	//LAUREL,

	//LIGHTENINGRING,
	//HOLYWATER,
	//FIVESTAR,

	// @@@ AttriBute : Passive @@@

	BRACER,			// + SWORD = THOUSANDEDGE
	//EMPTYTOME,		// + MAGICWAND = HOLYWAND
	//SPINACH,			// + FIREWAND = HELLFIRE
	//SPELLBINDER,		// + KINGBIBLE = UNHOLYVESPERS
	//HOLLOWHEART,		// + WHIP = BLOODYTEAR
	CLOVER,				// + CROSS = HEAVENSWORD
	//PUMMAROLA,			// + GARLIC = SOULEATER
	//CANDLELABRADOR,		// + AXE = DEATHSPIRAL
	//WING,

	MAX,

	// etc
	THOUSANDEDGE,
	HOLYWAND,
	HELLFIRE,
	UNHOLYVESPERS,
	BLOODYTEAR,
	HEAVENSWORD,
	SOULEATER,
	NONE, 
};