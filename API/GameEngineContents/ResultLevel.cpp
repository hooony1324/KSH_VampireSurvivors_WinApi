#include "ResultLevel.h"
#include "ResultBackGround.h"
#include "ResultBoard.h"


ResultLevel::ResultLevel() 
{
}

ResultLevel::~ResultLevel() 
{
}

void ResultLevel::Loading()
{

}

void ResultLevel::LevelChangeStart()
{
	CreateActor<ResultBackGround>("BackGround", 0);
	CreateActor<ResultBoard>("ResultBoard", 1);
}

void ResultLevel::Update()
{
}

