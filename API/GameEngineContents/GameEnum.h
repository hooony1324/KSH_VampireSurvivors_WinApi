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
const int ACTIVE_MAX = 5;
const int EVOLVE_MAX = 13;
enum class SkillType
{
	KNIFE,
	MAGICWAND,
	FIREWAND,
	KINGBIBLE,
	RUNETRACER,
	BRACER,			
	CLOVER,
	EMPTYTOME,
	SPINACH,
	WING,
	MAGNET,
	MAX,

	// ����
	THOUSANDEDGE,

	// etc
	NONE,
 
};