#include "TitleLevel.h"
#include "TitleBackGround.h"
#include "TitleLogo.h"
#include "GameEngine/GameEngine.h"

TitleLevel::TitleLevel() 
{
}

TitleLevel::~TitleLevel() 
{
}

void TitleLevel::Loading()
{
	CreateActor<TitleBackGround>("Title", 0);
	CreateActor<TitleLogo>("Title", 1);
}

void TitleLevel::LevelChangeStart()
{

}

void TitleLevel::Update()
{

}

