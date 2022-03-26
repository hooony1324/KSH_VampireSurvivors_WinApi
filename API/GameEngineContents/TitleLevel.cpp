#include "TitleLevel.h"
#include "TitleBackGround.h"
#include "TitleLogo.h"
#include "GameEngine/GameEngine.h"

enum class RENDER_ORDER
{
	BACKGROUND,
	UI,
};

TitleLevel::TitleLevel() 
{
}

TitleLevel::~TitleLevel() 
{
}

void TitleLevel::Loading()
{
	CreateActor<TitleBackGround>((int)RENDER_ORDER::BACKGROUND);
	CreateActor<TitleLogo>((int)RENDER_ORDER::UI);
}

void TitleLevel::LevelChangeStart()
{

}

void TitleLevel::Update()
{

}

