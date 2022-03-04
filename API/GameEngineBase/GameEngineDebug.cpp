#include "GameEngineDebug.h"

void GameEngineDebug::LeakCheckOn()
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
}

GameEngineDebug::GameEngineDebug()
{
}

GameEngineDebug::~GameEngineDebug() 
{
}

