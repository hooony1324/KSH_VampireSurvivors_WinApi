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

	// 리퍼는 버튼 누르면 소환되는 걸로 변경 -> BossNameList의 마지막 인덱스는 리퍼 
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

	// 이름대로 애니메이션 세팅
	SetRenderer(BossType_);
	

	// 보스 인덱스로 스탯 조정
	SetStat();

	// 콜리전 설정
	BossCol_ = CreateCollision("Boss", { 28, 45 });
	
	// 피격 
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

	//왼쪽 오른쪽 쳐다보기
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
	// 넉벡 벡터 줄이기 ~ 0 까지
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

	// 박스 떨굼
	GameEngineActor* Ptr = GetLevel()->CreateActor<LevelUpBox>(static_cast<int>(ACTOR_ORDER::UI));
	Ptr->SetPosition(BossPos_);

}

void Boss::DieUpdate()
{
	// 넉벡Dir 줄여야함
	// 넉벡 벡터 줄이기 ~ 0 까지
	float Distance = 20.0f;
	SetMove(KnockBackDir_ * DeltaTime_ * Distance * KnockBackRatio_);
	KnockBackDir_ *= 0.95f;


	// 넉벡 벡터 0이면 HitEnd
	if (0.05f > KnockBackDir_.Len2D())
	{
		KnockBackDir_ = float4::ZERO;
	}

	// Dead 애니메이션 종료시
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

	// 스폰 됐을 때콜리전 맵 안에 갇혀있으면 빠져나가야함
	int Trapped = ColorTop + ColorBot + ColorLeft + ColorRight;
	if (Trapped <= static_cast<int>(RGB(255, 255, 255)) * 1)
	{
		// 3개 이상이 RGB(0, 0, 0)인 경우(갇힘) 움직일 수 있다
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
	// 콜리전 Result
	if (nullptr == BossCol_)
	{
		return;
	}

	// 공격 충돌체크
	if (true == BossCol_->CollisionResult("PlayerAttack", PlayerAttack_))
	{
		PlayerAttack* Attack = dynamic_cast<PlayerAttack*>(PlayerAttack_[0]->GetActor());
		if (true == Attack->IsBullet())
		{
			// 원거리 공격이면 총알 없애야됨
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