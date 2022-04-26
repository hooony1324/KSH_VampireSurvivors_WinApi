#include "GameStartMenu.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>

#include "GameInfo.h"
#include "GameEnum.h"
#include "Counter.h"

#include <vector>

// Focus Direction

// Buttons
std::vector<std::vector<GameEngineRenderer*>> Buttons(3, std::vector<GameEngineRenderer*>(3, nullptr));
GameEngineRenderer* CurButton = nullptr;

ButtonPos CurrentButtonPos{0, 0};

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

	// 아무 키나 눌러주세요 블링크
	PressAnyKey_ = CreateRenderer("PressAnyKey.bmp", static_cast<int>(RENDER_ORDER::UI));

	// 스타트 메뉴
	ButtonStart_ = CreateRenderer("ButtonStart.bmp", static_cast<int>(RENDER_ORDER::UI));
	ButtonPowerUp_ = CreateRenderer("ButtonPowerUp.bmp", static_cast<int>(RENDER_ORDER::UI));
	ButtonChallenge_ = CreateRenderer("ButtonChallenge.bmp", static_cast<int>(RENDER_ORDER::UI));
	ButtonCollection_ = CreateRenderer("ButtonCollection.bmp", static_cast<int>(RENDER_ORDER::UI));
	ButtonCrew_ = CreateRenderer("ButtonCrew.bmp", static_cast<int>(RENDER_ORDER::UI));

	ButtonStart_->Off();
	ButtonStart_->SetPivot({ 0, 110 });
	Buttons[0][1] = ButtonStart_;

	ButtonCollection_->Off();
	ButtonCollection_->SetPivot({ -210, 250 });
	Buttons[1][0] = ButtonCollection_;

	ButtonPowerUp_->Off();
	ButtonPowerUp_->SetPivot({ 0, 250 });
	Buttons[1][1] = ButtonPowerUp_;

	ButtonChallenge_->Off();
	ButtonChallenge_->SetPivot({ 210, 250 });
	Buttons[1][2] = ButtonChallenge_;

	ButtonCrew_->Off();
	ButtonCrew_->SetPivot({ 0, 370 });
	Buttons[2][1] = ButtonCrew_;

	ArrowL_ = CreateRenderer();
	ArrowL_->CreateAnimation("Arrow_R.bmp", "ArrowR", 0, 7, 0.1f, true);
	ArrowL_->ChangeAnimation("ArrowR");
	ArrowL_->Off();

	ArrowR_ = CreateRenderer();
	ArrowR_->CreateAnimation("Arrow_L.bmp", "ArrowL", 0, 7, 0.1f, true);
	ArrowR_->ChangeAnimation("ArrowL");
	ArrowR_->Off();

	// 캐릭터 선택 메뉴


	// 맵 선택 메뉴


	ChangeState(STATE::ANYKEY);
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
		BlinkEnd();
		ChangeState(STATE::START);
	}
}

void GameStartMenu::BlinkEnd()
{
	PressAnyKey_->Off();
	AnyKeyActivated_ = false;
	BlinkOn_ = false;
}

// ANYKEY RENDER
void GameStartMenu::BlinkAnyKey()
{
	if (false == AnyKeyActivated_)
	{
		return;
	}

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
	ButtonStart_->On();
	ButtonCollection_->On();
	ButtonPowerUp_->On();
	ButtonChallenge_->On();
	ButtonCrew_->On();

	CurrentButtonPos = { 0, 1 };
}

void GameStartMenu::ButtonsUpdate()
{
	// 애로우
	CurButton = Buttons[CurrentButtonPos.y][CurrentButtonPos.x];

	// 입력
	if (true == GameEngineInput::GetInst()->IsDown("MoveLeft"))
	{
		SetNextButton(0, -1);
	}
	if (true == GameEngineInput::GetInst()->IsDown("MoveRight"))
	{
		SetNextButton(0, 1);
	}
	if (true == GameEngineInput::GetInst()->IsDown("MoveUp"))
	{
		SetNextButton(-1, 0);
	}
	if (true == GameEngineInput::GetInst()->IsDown("MoveDown"))
	{
		SetNextButton(1, 0);
	}

	if (true == GameEngineInput::GetInst()->IsDown("SpaceBar"))
	{
		// 현재 버튼 위치
		if (ButtonPos{ 0, 1 } == CurrentButtonPos)
		{
			// StartButton 누름
			ButtonsEnd();
			CurButton = nullptr;
			ChangeState(STATE::SELECT_CHARACTER);
		}
	}

	// 애로우 표시, Buttons일때만
	if (nullptr != CurButton)
	{
		ArrowL_->On();
		ArrowR_->On();

		ArrowL_->SetPivot(CurButton->GetPivot() + float4{ -CurButton->GetScale().Half().x - 20, 0 });
		ArrowR_->SetPivot(CurButton->GetPivot() + float4{ CurButton->GetScale().Half().x + 20, 0 });
	}
	else
	{
		ArrowL_->Off();
		ArrowR_->Off();
	}

}

void GameStartMenu::ButtonsEnd()
{
	ButtonStart_->Off();
	ButtonCollection_->Off();
	ButtonPowerUp_->Off();
	ButtonChallenge_->Off();
	ButtonCrew_->Off();

	CurrentButtonPos = { 0, 1 };
}

bool GameStartMenu::SetNextButton(int _y, int _x)
{
	int NewY = CurrentButtonPos.y + _y;
	int NewX = CurrentButtonPos.x + _x;

	if (NewX < 0 || NewX >= 3 || NewY < 0 || NewY >= 3)
	{
		return false;
	}

	if (nullptr == Buttons[NewY][NewX])
	{
		return false;
	}
	else
	{
		CurrentButtonPos = { NewY, NewX };
	}

	return true;
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
