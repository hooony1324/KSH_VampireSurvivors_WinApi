#include "GameEngineLevel.h"
#include "GameEngineActor.h"

GameEngineLevel::GameEngineLevel() 
{
}

GameEngineLevel::~GameEngineLevel() 
{
	std::map<int, std::list<GameEngineActor*>>::iterator GroupStart;
	std::map<int, std::list<GameEngineActor*>>::iterator GroupEnd;

	for (; GroupStart != GroupEnd; ++GroupStart)
	{
		std::list<GameEngineActor*>& Group = GroupStart->second;

		std::list<GameEngineActor*>::iterator StartActor = Group.begin();
		std::list<GameEngineActor*>::iterator EndActor = Group.end();
		
		for (; StartActor != EndActor; ++StartActor)
		{
			if (nullptr == (*StartActor))
			{
				continue;
			}
			delete (*StartActor);
			(*StartActor) = nullptr;
		}
	}
}

void GameEngineLevel::ActorUpdate()
{
	std::map<int, std::list<GameEngineActor*>>::iterator GroupStart;
	std::map<int, std::list<GameEngineActor*>>::iterator GroupEnd;

	std::list<GameEngineActor*>::iterator StartActor;
	std::list<GameEngineActor*>::iterator EndActor;

	GroupStart = AllActor_.begin();
	GroupEnd = AllActor_.end();

	for (; GroupStart != GroupEnd; ++GroupStart)
	{
		std::list<GameEngineActor*>& Group = GroupStart->second;

		StartActor = Group.begin();
		EndActor = Group.end();

		for (; StartActor != EndActor; ++StartActor)
		{
			(*StartActor)->Update();
		}
	}

}

void GameEngineLevel::ActorRender()
{
	std::map<int, std::list<GameEngineActor*>>::iterator GroupStart;
	std::map<int, std::list<GameEngineActor*>>::iterator GroupEnd;

	std::list<GameEngineActor*>::iterator StartActor;
	std::list<GameEngineActor*>::iterator EndActor;
	
	GroupStart = AllActor_.begin();
	GroupEnd = AllActor_.end();

	for (; GroupStart != GroupEnd; ++GroupStart)
	{
		std::list<GameEngineActor*>& Group = GroupStart->second;

		// ·»´õ¸µÀ» °¢ÀÚ ´Ù ³¡³»°í ·»´õÇÑ´Ù.
		StartActor = Group.begin();
		EndActor = Group.end();
		for (; StartActor != EndActor; ++StartActor)
		{
			(*StartActor)->Rendering();
		}

		// ·»´õ
		StartActor = Group.begin();
		EndActor = Group.end();
		for (; StartActor != EndActor; ++StartActor)
		{
			(*StartActor)->Render();
		}
	}
}
