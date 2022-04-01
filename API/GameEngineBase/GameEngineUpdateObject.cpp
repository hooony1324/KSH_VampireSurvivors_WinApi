#include "GameEngineUpdateObject.h"

GameEngineUpdateObject::GameEngineUpdateObject() 
	: IsUpdate_(true)
	, IsDeath_(false)
	, IsReleaseUpdate_(false)
	, DeathTime_(0)
{
}

GameEngineUpdateObject::~GameEngineUpdateObject() 
{
}

