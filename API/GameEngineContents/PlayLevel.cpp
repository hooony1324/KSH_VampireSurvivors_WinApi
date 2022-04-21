#include "PlayLevel.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineCollision.h>

#include "GameEnum.h"
#include "PlayLevelContents.h"
#include "GameInfo.h"

float MapLeftX = 700;
float MapRightX = 2940;

PlayLevel::PlayLevel()
	: Player_(nullptr)
	, Map_(nullptr)
	, PlayLevelPause_(false)
	, EnemyController_(nullptr)
	, ExpUI_(nullptr)
	, WeaponUI_(nullptr)
	, TimerUI_(nullptr)
	, CoinUI_(nullptr)
	, LevelUI_(nullptr)
	, KillCountUI_(nullptr)
	, PauseUI_(nullptr)
	, StatUI_(nullptr)
{
}

PlayLevel::~PlayLevel() 
{
}

// �̸� �ε��صθ� ����
void PlayLevel::Loading()
{

}

// ���� ����� ���� (Title -> Play -> Result)
// ��, ĳ����, .. �� ���� �Ǹ� �ش��ϴ� ������ ���͸� �����ؾ� ��
void PlayLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{	
	DebugModeOff();

	// �ð� ����
	GameEngineTime::GetInst()->SetTimeScale(static_cast<int>(TIME_GROUP::MONSTER), 1.0f);
	GameEngineTime::GetInst()->SetTimeScale(static_cast<int>(TIME_GROUP::PLAYER), 1.0f);
	GameEngineTime::GetInst()->SetTimeScale(static_cast<int>(TIME_GROUP::WEAPON), 1.0f);

	// ��
	CreateMap();	

	// ���� ������ 
	EnemyController_ = CreateActor<EnemyController>(static_cast<int>(RENDER_ORDER::MONSTER), "EnemyController");


	// �÷��̾�
	Player_ = CreateActor<Player>(static_cast<int>(RENDER_ORDER::PLAYER), "Player");

	// UI
	ExpUI_ = CreateActor<ExpBar>(static_cast<int>(RENDER_ORDER::UI), "UI");
	WeaponUI_ = CreateActor<WeaponSlots>(static_cast<int>(RENDER_ORDER::UI), "UI");
	TimerUI_ = CreateActor<TimerUI>(static_cast<int>(RENDER_ORDER::UI), "UI");
	CoinUI_ = CreateActor<CoinUI>(static_cast<int>(RENDER_ORDER::UI), "UI");
	LevelUI_ = CreateActor<LevelUI>(static_cast<int>(RENDER_ORDER::UI), "UI");
	KillCountUI_ = CreateActor<KillCountUI>(static_cast<int>(RENDER_ORDER::UI), "UI");

	PauseUI_ = CreateActor<PauseUI>(static_cast<int>(RENDER_ORDER::UI), "UI");
	StatUI_ = CreateActor<StatUI>(static_cast<int>(RENDER_ORDER::UI), "UI");
	
	PauseUI_->Off();
	StatUI_->Off();



	//BgmPlayer = GameEngineSound::SoundPlayControl("bgm_elrond_library_quiet.MP3");

	// ������ 
	ExpGem* FirstGem = CreateActor<ExpGem>(static_cast<int>(ACTOR_ORDER::ITEM), "ITEM");
	FirstGem->SetPosition({ 1000, 500 });
	FirstGem->SetType(GemType::GREEN);


	// �׽�Ʈ�� ������
	Coin* FirstCoin = CreateActor<Coin>(static_cast<int>(ACTOR_ORDER::ITEM), "ITEM");
	FirstCoin->SetPosition({ 1000, 1000 });
	
	for (int i = 0; i < 10; i++)
	{
		LevelUpBox* Box = CreateActor<LevelUpBox>(static_cast<int>(ACTOR_ORDER::ITEM), "ITEM");
		Box->SetPosition(float4{ 1100 , 1000 } + float4{ static_cast<float>(i) * 50, 0 });
	}
	

}

void PlayLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	ExpUI_->Death();
	WeaponUI_->Death();

	TimerUI* Ptr = dynamic_cast<TimerUI*>(TimerUI_);
	Ptr->KillDigits();
	TimerUI_->Death();

	CoinUI_->Death();
	LevelUI_->Death();
	KillCountUI_->Death();
	PauseUI_->Death();

	Player_->Death();
	Map_->Death();
	EnemyController_->Death();


	//BgmPlayer.Stop();

}

void PlayLevel::Update()
{
	LevelUpUICheck();

	// Key Check
	if (true == GameEngineInput::GetInst()->IsDown("ChangeLevelNext"))
	{
		GameEngine::GetInst().ChangeLevel("Result");
	}

	if (true == GameEngineInput::GetInst()->IsDown("ColDebugger"))
	{
		DebugModeSwitch();
	}

	// �Ͻ����� ���
	GamePause();

	ShowPauseMenu();

	InfiniteMap();

	//EnemyController_->();


}

void PlayLevel::GamePause()
{
	if (true == GameInfo::IsPause())
	{
		GameEngineTime::GetInst()->SetTimeScale(static_cast<int>(TIME_GROUP::MONSTER), 0.0f);
		GameEngineTime::GetInst()->SetTimeScale(static_cast<int>(TIME_GROUP::PLAYER), 0.0f);
		GameEngineTime::GetInst()->SetTimeScale(static_cast<int>(TIME_GROUP::WEAPON), 0.0f);
		GameEngineTime::GetInst()->SetTimeScale(static_cast<int>(TIME_GROUP::TIMER), 0.0f);
	}
	else
	{
		GameEngineTime::GetInst()->SetTimeScale(static_cast<int>(TIME_GROUP::MONSTER), 1.0f);
		GameEngineTime::GetInst()->SetTimeScale(static_cast<int>(TIME_GROUP::PLAYER), 1.0f);
		GameEngineTime::GetInst()->SetTimeScale(static_cast<int>(TIME_GROUP::WEAPON), 1.0f);
		GameEngineTime::GetInst()->SetTimeScale(static_cast<int>(TIME_GROUP::TIMER), 1.0f);
	}
}

void PlayLevel::ShowPauseMenu()
{
	if ( true == LevelUpUI::IsActivated())
	{
		return;
	}

	if (true == GameEngineInput::GetInst()->IsDown("Esc"))
	{
		PlayLevelPause_ = !PlayLevelPause_;
		GameInfo::SetPause(PlayLevelPause_);

		if (false == GameInfo::IsPause())
		{
			PauseUI_->Off();
			StatUI_->Off();
		}
		else
		{
			PauseUI_->On();
			StatUI_->On();
		}
	}

}

void PlayLevel::LevelUpUICheck()
{
	if (LevelUpUI::CreateCount_ <= 0)
	{
		return;
	}

	if (false == LevelUpUI::IsActivated())
	{
		CreateActor<LevelUpUI>(static_cast<int>(ACTOR_ORDER::UI), "UI");
	}
}

void PlayLevel::CreateMap()
{
	Map_ = CreateActor<Library>(static_cast<int>(RENDER_ORDER::MONSTER), "Library");
	// ������ ��ġ, ũ�� ����
	Map_->SetPosition(float4::ZERO);
	Map_->SetScale(Map_->GetRendererScale());

}

void PlayLevel::InfiniteMap()
{
	Map_->CheckPlayerOnEnd();
}
