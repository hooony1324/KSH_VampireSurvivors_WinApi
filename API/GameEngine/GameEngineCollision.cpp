#include "GameEngineCollision.h"
#include "GameEngine.h"
#include "GameEngineLevel.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineTime.h>

bool (*CollisionCheckArray[static_cast<int>(CollisionType::Max)][static_cast<int>(CollisionType::Max)])(GameEngineCollision*, GameEngineCollision*);

bool RectToRect(GameEngineCollision* _Left, GameEngineCollision* _Right)
{
	if (nullptr == _Left || nullptr == _Right)
	{
		return false;
	}

	GameEngineRect LeftRc = _Left->GetRect();
	GameEngineRect RightRc = _Right->GetRect();

	return LeftRc.OverLap(RightRc);
}


class CollisionInit
{
public:
	CollisionInit()
	{
		CollisionCheckArray[static_cast<int>(CollisionType::Rect)][static_cast<int>(CollisionType::Rect)] = RectToRect;
	}
};

CollisionInit InitInst = CollisionInit();

GameEngineCollision::GameEngineCollision()
	: Pivot_(float4::ZERO),
	Scale_(float4::ZERO),
	IsCameraEffect_(true)
{
	// 
}

GameEngineCollision::~GameEngineCollision()
{
}

bool GameEngineCollision::CollisionCheck(
	const std::string& _TargetGroup,
	CollisionType _This /*= CollisionType::Circle*/,
	CollisionType _Target /*= CollisionType::Rect*/
)
{
	if (false == IsUpdate() || true == IsDeath())
	{
		return false;
	}

	std::map<std::string, std::list<GameEngineCollision*>>::iterator FindTargetGroup = GetActor()->GetLevel()->AllCollision_.find(_TargetGroup);

	if (FindTargetGroup == GetActor()->GetLevel()->AllCollision_.end())
	{
		// MsgBoxAssert("존재하지 않는 충돌 그룹과 충돌하려고 했습니다.");

		return false;
	}

	if (nullptr == CollisionCheckArray[static_cast<int>(_This)][static_cast<int>(_Target)])
	{
		MsgBoxAssert("처리할수 없는 충돌체크 조합입니다.");
		return false;
	}

	std::list<GameEngineCollision*>& TargetGroup = FindTargetGroup->second;

	std::list<GameEngineCollision*>::iterator StartIter = TargetGroup.begin();
	std::list<GameEngineCollision*>::iterator EndIter = TargetGroup.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (false == (*StartIter)->IsUpdate() || true == (*StartIter)->IsDeath())
		{
			continue;
		}

		if (CollisionCheckArray[static_cast<int>(_This)][static_cast<int>(_Target)](this, *StartIter))
		{
			return true;
		}
	}

	return false;
}

bool GameEngineCollision::NextPosCollisionCheck(
	const std::string& _TargetGroup,
	float4 _NextPos,
	CollisionType _This /*= CollisionType::Circle*/,
	CollisionType _Target /*= CollisionType::Circle*/
)
{
	if (false == IsUpdate() || true == IsDeath())
	{
		return false;
	}

	std::map<std::string, std::list<GameEngineCollision*>>::iterator FindTargetGroup = GetActor()->GetLevel()->AllCollision_.find(_TargetGroup);

	if (FindTargetGroup == GetActor()->GetLevel()->AllCollision_.end())
	{
		// MsgBoxAssert("존재하지 않는 충돌 그룹과 충돌하려고 했습니다.");

		return false;
	}

	if (nullptr == CollisionCheckArray[static_cast<int>(_This)][static_cast<int>(_Target)])
	{
		MsgBoxAssert("처리할수 없는 충돌체크 조합입니다.");
		return false;
	}

	std::list<GameEngineCollision*>& TargetGroup = FindTargetGroup->second;

	std::list<GameEngineCollision*>::iterator StartIter = TargetGroup.begin();
	std::list<GameEngineCollision*>::iterator EndIter = TargetGroup.end();

	NextPos_ = _NextPos;

	for (; StartIter != EndIter; ++StartIter)
	{
		if (false == (*StartIter)->IsUpdate() || true == (*StartIter)->IsDeath())
		{
			continue;
		}

		if (CollisionCheckArray[static_cast<int>(_This)][static_cast<int>(_Target)](this, *StartIter))
		{
			return true;
		}
	}

	NextPosReset();

	return false;
}

void GameEngineCollision::DebugRender()
{
	if (false == IsUpdate() || true == IsDeath())
	{
		return;
	}

	float4 Pos = GetActor()->GetPosition();

	if (true == IsCameraEffect_)
	{
		Pos = GetActor()->GetCameraEffectPosition();
	}
	GameEngineRect DebugRect(Pos + Pivot_, Scale_);

	Rectangle(
		GameEngine::BackBufferDC(),
		DebugRect.CenterLeft(),
		DebugRect.CenterTop(),
		DebugRect.CenterRight(),
		DebugRect.CenterBot()
	);

}

bool GameEngineCollision::CollisionResult(
	const std::string& _TargetGroup,
	std::vector<GameEngineCollision*>& _ColResult,
	CollisionType _This /*= CollisionType::Circle*/,
	CollisionType _Target /*= CollisionType::Circle*/
)
{
	if (false == IsUpdate() || true == IsDeath())
	{
		return false;
	}

	size_t StartSize = _ColResult.size();

	std::map<std::string, std::list<GameEngineCollision*>>::iterator FindTargetGroup = GetActor()->GetLevel()->AllCollision_.find(_TargetGroup);

	if (FindTargetGroup == GetActor()->GetLevel()->AllCollision_.end())
	{
		// MsgBoxAssert("존재하지 않는 충돌 그룹과 충돌하려고 했습니다.");

		return false;
	}

	if (nullptr == CollisionCheckArray[static_cast<int>(_This)][static_cast<int>(_Target)])
	{
		MsgBoxAssert("처리할수 없는 충돌체크 조합입니다.");
		return false;
	}

	std::list<GameEngineCollision*>& TargetGroup = FindTargetGroup->second;

	std::list<GameEngineCollision*>::iterator StartIter = TargetGroup.begin();
	std::list<GameEngineCollision*>::iterator EndIter = TargetGroup.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (false == (*StartIter)->IsUpdate() || true == (*StartIter)->IsDeath())
		{
			continue;
		}


		if (CollisionCheckArray[static_cast<int>(_This)][static_cast<int>(_Target)](this, *StartIter))
		{
			_ColResult.push_back(*StartIter);
		}
	}

	return StartSize != _ColResult.size();
}