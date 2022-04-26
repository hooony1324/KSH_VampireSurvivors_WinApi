#include "GameStartMenu.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineSound.h>

#include "GameEnum.h"
#include "Counter.h"

#include <vector>
#include <string>

// START
std::vector<std::vector<GameEngineRenderer*>> Buttons(3, std::vector<GameEngineRenderer*>(3, nullptr));
GameEngineRenderer* CurButton = nullptr;
ButtonPos CurrentButtonPos{0, 0};

// SELECT_CHARACTER
const int CharacterNum = static_cast<int>(CharacterType::MAX);
std::vector<GameEngineRenderer*> Characters(CharacterNum, nullptr);
bool CharacterFocusedOn[CharacterNum] = { false, };		// 한번 더 선택하면 활성화시키기 위함

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

	// START 메뉴
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

	// SELECT_CHARACTER 메뉴
	CharacterSelectBackGround_ = CreateRenderer("CharacterSelectUI.bmp", static_cast<int>(RENDER_ORDER::UI));
	CharacterSelectBackGround_->SetPivot({ 0, 38 });
	CharacterSelectBackGround_->Off();
	
	// 최초위치
	CurCharacterIndex_ = 0;

	// - 캐릭터 버튼 위치 조정
	float4 TopLeft = float4{ -215, -178 };

	for (int i = 0; i < static_cast<int>(CharacterType::MAX); i++)
	{
		std::string Name = CharacterNameList[i];
		Characters_[i] = CreateRenderer("CharacterButton_"+ Name + ".bmp", static_cast<int>(RENDER_ORDER::UI));
		Characters_[i]->Off();
		Characters_[i]->SetPivot(TopLeft + float4{ (Characters_[i]->GetScale().x * i) + (18 * i), 0 });
	}

	// - 캐릭터 설명 UI
	TopLeft = { 1, 325 };
	CurCharacterInfoAndButton_ = CreateRenderer("CharacterButton_" + CharacterNameList[CurCharacterIndex_] + ".bmp", static_cast<int>(RENDER_ORDER::UI));
	CurCharacterInfoAndButton_->SetPivot(TopLeft);
	CurCharacterInfoAndButton_->Off();

	// SELECT_MAP 메뉴



	// 최초 상태
	ChangeState(STATE::ANYKEY);
}

void GameStartMenu::Update()
{
	StateUpdate();


}

void GameStartMenu::Render()
{
	if (true == AnyKeyActivated_)
	{
		BlinkAnyKey();
		RenderAnyKey();
	}


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
		FocusNextButton(0, -1);
	}
	if (true == GameEngineInput::GetInst()->IsDown("MoveRight"))
	{
		FocusNextButton(0, 1);
	}
	if (true == GameEngineInput::GetInst()->IsDown("MoveUp"))
	{
		FocusNextButton(-1, 0);
	}
	if (true == GameEngineInput::GetInst()->IsDown("MoveDown"))
	{
		FocusNextButton(1, 0);
	}

	if (true == GameEngineInput::GetInst()->IsDown("SpaceBar"))
	{
		// 현재 버튼 위치
		if (ButtonPos{ 0, 1 } == CurrentButtonPos)
		{
			// StartButton 누름
			GameEngineSound::SoundPlayOneShot("ButtonDown.mp3", 0);
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

bool GameStartMenu::FocusNextButton(int _y, int _x)
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
	CharacterSelectBackGround_->On();

	for (int i = 0; i < static_cast<int>(CharacterType::MAX); i++)
	{
		Characters_[i]->On();
	}

	CurCharacterInfoAndButton_->On();

	for (int i = 0; i < static_cast<int>(CharacterType::MAX); i++)
	{
		CharacterFocusedOn[i] = false;
	}

}

void GameStartMenu::SelectCharacterUpdate()
{
	if (true == CharacterFocusedOn[CurCharacterIndex_])
	{
		Characters_[CurCharacterIndex_]->SetImage("CharacterButtonFocusedOn_" + CharacterNameList[CurCharacterIndex_] + ".bmp");
		CurCharacterInfoAndButton_->SetImage("CharacterInfoAndButtonOn_" + CharacterNameList[CurCharacterIndex_] + ".bmp");
	}
	else
	{
		Characters_[CurCharacterIndex_]->SetImage("CharacterButtonFocused_" + CharacterNameList[CurCharacterIndex_] + ".bmp");
		CurCharacterInfoAndButton_->SetImage("CharacterInfoAndButton_" + CharacterNameList[CurCharacterIndex_] + ".bmp");
	}

	// 입력
	if (true == GameEngineInput::GetInst()->IsDown("MoveLeft"))
	{
		FocusNextCharacter(-1);
	}
	if (true == GameEngineInput::GetInst()->IsDown("MoveRight"))
	{
		FocusNextCharacter(1);
	}

	if (true == GameEngineInput::GetInst()->IsDown("SpaceBar"))
	{
		// 포커스 상태 false 면 true로 바꾸고 
		if (false == CharacterFocusedOn[CurCharacterIndex_])
		{
			GameEngineSound::SoundPlayOneShot("ButtonDown.mp3", 0);
			CharacterFocusedOn[CurCharacterIndex_] = true;
		}
		else
		{
			// 맵 선택으로 넘어감
			GameEngineSound::SoundPlayOneShot("ButtonDown.mp3", 0);
			ChangeState(STATE::SELECT_MAP);
			GameInfo::SetCharacter(static_cast<CharacterType>(CurCharacterIndex_));
			SelectCharacterEnd();
			GameEngine::GetInst().ChangeLevel("Play");
		}
	}

}

void GameStartMenu::SelectCharacterEnd()
{
	CharacterSelectBackGround_->Off();

	for (int i = 0; i < static_cast<int>(CharacterType::MAX); i++)
	{
		Characters_[i]->Off();
	}

	CurCharacterInfoAndButton_->Off();
}

void GameStartMenu::FocusNextCharacter(int _x)
{
	int NextFocusPos = CurCharacterIndex_ + _x;
	if (0 > NextFocusPos || static_cast<int>(CharacterType::MAX) <= NextFocusPos)
	{
		return;
	}

	// 원래이미지로 돌려놓고
	Characters_[CurCharacterIndex_]->SetImage("CharacterButton_" + CharacterNameList[CurCharacterIndex_] + ".bmp");

	// 만약 Focused상태였다면 돌려놓고
	if (true == CharacterFocusedOn[CurCharacterIndex_])
	{
		CharacterFocusedOn[CurCharacterIndex_] = false;
	}

	// 인덱스 변경
	CurCharacterIndex_ = NextFocusPos;

}

// SELECT_MAP
void GameStartMenu::SelectMapStart()
{

}

void GameStartMenu::SelectMapUpdate()
{

}

void GameStartMenu::SelectMapEnd()
{
}
