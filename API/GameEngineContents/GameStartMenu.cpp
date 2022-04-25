#include "GameStartMenu.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>

#include "GameEnum.h"
#include "Counter.h"

GameStartMenu::GameStartMenu() 
{
}

GameStartMenu::~GameStartMenu() 
{
}

void GameStartMenu::Start()
{
	NextLevelOff();

	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale(GameEngineWindow::GetScale());

	// 시작 상태
	CurState_ = STATE::ANYKEY;

	// 아무 키나 눌러주세요 블링크
	PressAnyKey_ = CreateRenderer("PressAnyKey.bmp", static_cast<int>(RENDER_ORDER::UI));

	
}

void GameStartMenu::Update()
{
	StateUpdate();

}

void GameStartMenu::Render()
{
	BlinkAnyKey();
	RenderAnyKey();

}

void GameStartMenu::StateUpdate()
{
	switch (CurState_)
	{
	case STATE::ANYKEY:
		BlinkUpdate();
		break;
	case STATE::START:
		ButtonsUpdate();
		break;
	case STATE::SELECT_CHARACTER:
		SelectCharacterUpdate();
		break;
	case STATE::SELECT_MAP:
		SelectMapUpdate();
		break;

	default:
		break;
	}
}

void GameStartMenu::ChangeState(STATE _State)
{
	if (CurState_ != _State)
	{
		switch (_State)
		{
		case STATE::ANYKEY:
			BlinkStart();
			break;
		case STATE::START:
			ButtonsStart();
			break;
		case STATE::SELECT_CHARACTER:
			SelectCharacterStart();
			break;
		case STATE::SELECT_MAP:
			SelectMapStart();
			break;
		default:
			break;
		}
	}

	CurState_ = _State;
}

// FSM STATE
// ANYKEY
void GameStartMenu::BlinkStart()
{
	PressAnyKey_->Off();
	AnyKeyActivated_ = true;
	BlinkCounter_.SetCount(0.64f);
	BlinkOn_ = false;
}

void GameStartMenu::BlinkUpdate()
{
	if (true == GameEngineInput::GetInst()->IsPress("SpaceBar"))
	{
		ChangeState(STATE::START);
	}

	BlinkAnyKey();
}

void GameStartMenu::BlinkAnyKey()
{
	if (true == BlinkCounter_.Start(GameEngineTime::GetDeltaTime()))
	{
		BlinkOn_ = !BlinkOn_;
		BlinkCounter_.Reset();
	}
}

void GameStartMenu::RenderAnyKey()
{
	if (true == BlinkOn_)
	{
		PressAnyKey_->On();
	}
	else
	{
		PressAnyKey_->Off();
	}
}

// START
void GameStartMenu::ButtonsStart()
{


}

void GameStartMenu::ButtonsUpdate()
{


}

// SELECT_CHARACTER
void GameStartMenu::SelectCharacterStart()
{
}

void GameStartMenu::SelectCharacterUpdate()
{
}

// SELECT_MAP
void GameStartMenu::SelectMapStart()
{
}

void GameStartMenu::SelectMapUpdate()
{
}
