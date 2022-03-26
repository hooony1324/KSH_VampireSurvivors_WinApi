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
	CreateActor<ResultBackGround>(0);
	CreateActor<ResultBoard>(0);
}

void ResultLevel::Update()
{
}

