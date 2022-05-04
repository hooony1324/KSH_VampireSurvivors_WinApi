#include "Boss.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineSound.h>

#include "GameInfo.h"
#include "LevelUpBox.h"
#include "Vector2D.h"
#include "PlayLevel.h"
#include "Player.h"
#include <vector>
#include "PlayerAttack.h"

std::vector<std::string> BossNameList = { "XLMummy", "XLReaper"};
int Boss::BossIndex_ = 0;
bool Boss::IsReaperSpawn_ = false;

Boss::Boss() 
{
}

Boss::~Boss() 
{
}

void Boss::Start()
{
	NextLevelOff();
	MapColImage_ = PlayLevel::MapColImage_;

	// ���۴� ��ư ������ ��ȯ�Ǵ� �ɷ� ���� -> BossNameList�� ������ �ε����� ���� 
	if (BossIndex_ >= BossNameList.size() - 1)
	{
		BossIndex_ = 0;
	}

	if (true == IsReaperSpawn_)
	{
		BossName_ = BossNameList[static_cast<int>(BOSSTYPE::XLRREAPER)];
		BossType_ = BOSSTYPE::XLRREAPER;
	}
	else
	{
		BossName_ = BossNameList[BossIndex_];
		BossType_ = static_cast<BOSSTYPE>(BossIndex_);
	}

	Renderer_ = CreateRenderer();

	// �̸���� �ִϸ��̼� ����
	SetRenderer(BossType_);
	

	// ���� �ε����� ���� ����
	SetStat();

	// �ݸ��� ����
	BossCol_ = CreateCollision("Boss", { 28, 45 });
	
	// �ǰ� 
	KnockBackRatio_ = 1.0f;
	HitCounter_.SetCount(0.3f);


	ChangeState(BOSS_STATE::CHASE);

}

void Boss::Update()
{
	DeltaTime_ = GameEngineTime::GetDeltaTime(static_cast<int>(TIME_GROUP::MONSTER));
	BossPos_ = GetPosition();

	UpdateState();
	BlockEnemies();
}

void Boss::Render()
{

}



void Boss::UpdateState()
{
	switch (State_)
	{
	case BOSS_STATE::CHASE:
		ChaseUpdate();
		break;
	case BOSS_STATE::HIT:
		HitUpdate();
		break;
	case BOSS_STATE::DIE:
		DieUpdate();
		break;
	default:
		break;
	}
}

void Boss::ChangeState(BOSS_STATE _State)
{
	if (State_ != _State)
	{
		switch (_State)
		{
		case BOSS_STATE::HIT:
			HitStart();
			break;
		case BOSS_STATE::DIE:
			DieStart();
			break;
		default:
			break;
		}
	}

	State_ = _State;
}

void Boss::ChaseUpdate()
{
	PlayerPos_ = GameInfo::GetPlayerInfo()->PlayerPos_;
	float4 DestDir = Vector2D::GetDirection(BossPos_, PlayerPos_);

	float Speed = MapColCheck(Speed_, DestDir);
	SetMove(DestDir * DeltaTime_ * Speed);

	HitCheck();

	//���� ������ �Ĵٺ���
	if (0 >= DestDir.x)
	{
		Renderer_->ChangeAnimation(BossName_ + "_WalkLeft");
	}
	else
	{
		Renderer_->ChangeAnimation(BossName_ + "_WalkRight");
	}


}

void Boss::HitStart()
{
	GameEngineSound::SoundPlayOneShot("EnemyHit.mp3", 0);
	Hp_ -= HitDamage_;

}

void Boss::HitUpdate()
{
	// �˺� ���� ���̱� ~ 0 ����
	float Distance = 40.0f;
	SetMove(KnockBackDir_ * DeltaTime_ * Distance * KnockBackRatio_);
	KnockBackDir_ *= 0.90f;

	if (true == HitCounter_.Start(GameEngineTime::GetDeltaTime(static_cast<int>(TIME_GROUP::MONSTER))))
	{
		HitEnd();
	}

}

void Boss::HitEnd()
{
	if (0.0f >= Hp_)
	{
		ChangeState(BOSS_STATE::DIE);
		return;
	}

	ChangeState(BOSS_STATE::CHASE);



}

void Boss::DieStart()
{
	GameInfo::GetPlayerInfo()->KillCount_ += 1;
	Renderer_->ChangeAnimation(BossName_ + "_Dead");
	BossCol_->Off();

	// �ڽ� ����
	GameEngineActor* Ptr = GetLevel()->CreateActor<LevelUpBox>(static_cast<int>(ACTOR_ORDER::UI));
	Ptr->SetPosition(BossPos_);

}

void Boss::DieUpdate()
{
	// �˺�Dir �ٿ�����
	// �˺� ���� ���̱� ~ 0 ����
	float Distance = 20.0f;
	SetMove(KnockBackDir_ * DeltaTime_ * Distance * KnockBackRatio_);
	KnockBackDir_ *= 0.95f;


	// �˺� ���� 0�̸� HitEnd
	if (0.05f > KnockBackDir_.Len2D())
	{
		KnockBackDir_ = float4::ZERO;
	}

	// Dead �ִϸ��̼� �����
	if (true == Renderer_->IsEndAnimation())
	{
		DieEnd();
	}
}

void Boss::DieEnd()
{
	Death();
}




float Boss::MapColCheck(float _Speed, float4 _DestDir)
{

	int BossPosX = GetPosition().ix() % MapColImage_->GetScale().ix();
	if (BossPosX < 0)
	{
		BossPosX = BossPosX + MapColImage_->GetScale().ix();
	}

	float4 BossMapColPos = { static_cast<float>(BossPosX), GetPosition().y };
	int ColorTop = MapColImage_->GetImagePixel(BossMapColPos + float4{ 0, -25 });
	int ColorBot = MapColImage_->GetImagePixel(BossMapColPos + float4{ 0, 25 });
	int ColorLeft = MapColImage_->GetImagePixel(BossMapColPos + float4{ -25, 0 });
	int ColorRight = MapColImage_->GetImagePixel(BossMapColPos + float4{ 25, 0 });

	// ���� ���� ���ݸ��� �� �ȿ� ���������� ������������
	int Trapped = ColorTop + ColorBot + ColorLeft + ColorRight;
	if (Trapped <= static_cast<int>(RGB(255, 255, 255)) * 1)
	{
		// 3�� �̻��� RGB(0, 0, 0)�� ���(����) ������ �� �ִ�
		return _Speed;
	}

	if (RGB(0, 0, 0) == ColorTop && _DestDir.y < 0.0f)
	{
		return 0.0f;
	}

	if (RGB(0, 0, 0) == ColorBot && _DestDir.y > 0.0f)
	{
		return 0.0f;
	}

	if (RGB(0, 0, 0) == ColorLeft && _DestDir.x < 0.0f)
	{
		return 0.0f;
	}

	if (RGB(0, 0, 0) == ColorRight && _DestDir.x > 0.0f)
	{
		return 0.0f;
	}

	return _Speed;
}

void Boss::BlockEnemies()
{
	if (true == BossCol_->CollisionResult("Enemy", Enemies_))
	{
		for (GameEngineCollision* EnemyCol : Enemies_)
		{
			GameEngineActor* Ptr = EnemyCol->GetActor();
			Ptr->SetMove(Vector2D::GetDirection(BossPos_, Ptr->GetPosition() * GameEngineTime::GetDeltaTime(static_cast<int>(TIME_GROUP::MONSTER)) * 85.0f));
		}
		Enemies_.clear();
	}
}

void Boss::HitCheck()
{
	// �ݸ��� Result
	if (nullptr == BossCol_)
	{
		return;
	}

	// ���� �浹üũ
	if (true == BossCol_->CollisionResult("PlayerAttack", PlayerAttack_))
	{
		PlayerAttack* Attack = dynamic_cast<PlayerAttack*>(PlayerAttack_[0]->GetActor());
		if (true == Attack->IsBullet())
		{
			// ���Ÿ� �����̸� �Ѿ� ���־ߵ�
			Attack->Death();
		}
		KnockBackDir_ = BossPos_ - Attack->GetPosition();
		HitDamage_ = Attack->GetDamage();
		PlayerAttack_.clear();
		ChangeState(BOSS_STATE::HIT);
	}

}

void Boss::SetStat()
{
	switch (BossType_)
	{
	case BOSSTYPE::XLMUMMY:
		Hp_ = 500.0f;
		Speed_ = 50.0f;
		KnockBackRatio_ = 0.6f;
		break;
	case BOSSTYPE::XLRREAPER:
		Hp_ = 10000.0f;
		Speed_ = 400.0f;
		KnockBackRatio_ = 0.1f;
		break;
	default:
		break;
	}
}

void Boss::SetRenderer(BOSSTYPE _BossType)
{
	switch (_BossType)
	{
	case BOSSTYPE::XLMUMMY:
		Renderer_->CreateFolderAnimationTimeKey(BossName_ + "_WalkLeft.bmp", BossName_ + "_WalkLeft", static_cast<int>(TIME_GROUP::MONSTER), 0, 3, 0.2f, true);
		Renderer_->CreateFolderAnimationTimeKey(BossName_ + "_WalkRight.bmp", BossName_ + "_WalkRight", static_cast<int>(TIME_GROUP::MONSTER), 0, 3, 0.2f, true);
		Renderer_->CreateFolderAnimationTimeKey(BossName_ + "_Dead.bmp", BossName_ + "_Dead", static_cast<int>(TIME_GROUP::MONSTER), 0, 29, 0.1f, false);
		Renderer_->ChangeAnimation(BossName_ + "_WalkLeft");
		break;
	case BOSSTYPE::XLRREAPER:
		Renderer_->CreateFolderAnimationTimeKey(BossName_ + "_WalkLeft.bmp", BossName_ + "_WalkLeft", static_cast<int>(TIME_GROUP::MONSTER), 0, 7, 0.2f, true);
		Renderer_->CreateFolderAnimationTimeKey(BossName_ + "_WalkRight.bmp", BossName_ + "_WalkRight", static_cast<int>(TIME_GROUP::MONSTER), 0, 7, 0.2f, true);
		Renderer_->CreateFolderAnimationTimeKey(BossName_ + "_Dead.bmp", BossName_ + "_Dead", static_cast<int>(TIME_GROUP::MONSTER), 0, 29, 0.1f, false);
		Renderer_->ChangeAnimation(BossName_ + "_WalkLeft");
		break;
	case BOSSTYPE::MAX:
		break;
	default:
		break;
	}
}