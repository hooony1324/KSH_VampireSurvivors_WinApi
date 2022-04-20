#include "GameEngineRenderer.h"
#include "GameEngineImageManager.h"
#include "GameEngine.h"
#include "GameEngineLevel.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineTime.h>

// 
// 11111111 00000000 11111111

#pragma comment(lib, "msimg32.lib")

GameEngineRenderer::GameEngineRenderer()
	: Image_(nullptr)
	, PivotType_(RenderPivot::CENTER)
	, ScaleMode_(RenderScaleMode::Image)
	, TransColor_(RGB(255, 0, 255))
	, RenderImagePivot_({ 0,0 })
	, IsCameraEffect_(true)
	, Alpha_(255)
	, RotZ_(0.0f)
{
}

GameEngineRenderer::~GameEngineRenderer()
{
}

void GameEngineRenderer::SetImageScale()
{
	if (nullptr == Image_)
	{
		MsgBoxAssert("�������� �ʴ� �̹����� ũ�⸦ �����Ϸ��� �߽��ϴ�.");
		return;
	}

	ScaleMode_ = RenderScaleMode::Image;
	RenderScale_ = Image_->GetScale();		// ȭ�� ��� ũ��, �̹��� ũ���
	RenderImageScale_ = Image_->GetScale();	// ���� �̹�����,  �̹��� ũ���
	RenderImagePivot_ = float4::ZERO;
}

void GameEngineRenderer::SetImage(const std::string& _Name)
{
	GameEngineImage* FindImage = GameEngineImageManager::GetInst()->Find(_Name);
	if (nullptr == FindImage)
	{
		MsgBoxAssertString(_Name + "�������� �ʴ� �̹����� �������� �����Ϸ��� �߽��ϴ�.");
		return;
	}

	Image_ = FindImage;
	SetImageScale();
}

void GameEngineRenderer::SetRotationFilter(const std::string& _Name)
{
	GameEngineImage * FindImage = GameEngineImageManager::GetInst()->Find(_Name);
	if (nullptr == FindImage)
	{
		MsgBoxAssertString(_Name + "�������� �ʴ� �̹����� �������� �����Ϸ��� �߽��ϴ�.");
		return;
	}

	RotationFilterImage_ = FindImage;
}


void GameEngineRenderer::Render()
{
	if (nullptr != CurrentAnimation_)	// CurAnimation�� nullptr�� �ƴϸ� �ִϸ��̼��� ������ �������̹Ƿ�
	{
		CurrentAnimation_->Update();	// 
	}

	if (nullptr == Image_)
	{
		MsgBoxAssert("�������� �̹����� ���õǾ� ���� ������ �������� �ȵ˴ϴ�.");
		return;
	}


	float4 RenderPos = GetActor()->GetPosition() + RenderPivot_;
	
	if (true == IsCameraEffect_)	// 
	{
		RenderPos -= GetActor()->GetLevel()->GetCameraPos();
	}


	switch (PivotType_)
	{
	case RenderPivot::CENTER:
		if (Alpha_ != 255)
		{
			GameEngine::BackBufferImage()->AlphaCopy(Image_, RenderPos - RenderScale_.Half(), RenderScale_, RenderImagePivot_, RenderImageScale_, Alpha_);
		}
		else if (RotZ_ != 0.0f)
		{

			GameEngine::BackBufferImage()->PlgCopy(Image_, RenderPos - RenderScale_.Half(), RenderScale_, RenderImagePivot_, RenderImageScale_, RotZ_, RotationFilterImage_);
			// GameEngine::BackBufferImage()->PlgCopy(Image_, RenderPos - RenderScale_.Half(), RenderScale_, RenderImagePivot_, RenderImageScale_, Alpha_);
		}
		else 
		{
			GameEngine::BackBufferImage()->TransCopy(Image_, RenderPos - RenderScale_.Half(), RenderScale_, RenderImagePivot_, RenderImageScale_, TransColor_);
		} 
		break;
	case RenderPivot::BOT:
	{
		float4 Scale = RenderScale_.Half();
		Scale.y *= 2;

		if (Alpha_ == 255)
		{
			GameEngine::BackBufferImage()->AlphaCopy(Image_, RenderPos - Scale, RenderScale_, RenderImagePivot_, RenderImageScale_, Alpha_);
		} 
		else if (RotZ_ != 0.0f)
		{
			GameEngine::BackBufferImage()->PlgCopy(Image_, RenderPos - Scale, RenderScale_, RenderImagePivot_, RenderImageScale_, RotZ_, RotationFilterImage_);
		}
		else 
		{
			GameEngine::BackBufferImage()->TransCopy(Image_, RenderPos - Scale, RenderScale_, RenderImagePivot_, RenderImageScale_, TransColor_);
		}

		
		break;
	}
	default:
		break;
	}
}

void GameEngineRenderer::SetIndex(size_t _Index, float4 _Scale)
{
	if (false == Image_->IsCut())
	{
		MsgBoxAssert("�̹����� �κ������� ����Ҽ� �ְ� �߷������� ���� �̹��� �Դϴ�.");
		return;
	}

	if (-1.0f == _Scale.x || -1.0f == _Scale.y)
	{
		RenderScale_ = Image_->GetCutScale(_Index);
	}
	else
	{
		RenderScale_ = _Scale;
	}

	RenderImagePivot_ = Image_->GetCutPivot(_Index);	// �̹����� ���°ĭ(������ �迭�� Index�� ����)�� �ش��ϴ� ��ǥ��
	RenderImageScale_ = Image_->GetCutScale(_Index);			// 
}

	// Animation
void GameEngineRenderer::CreateAnimation(
	const std::string& _Image,
	const std::string& _Name,
	int _StartIndex,
	int _EndIndex,
	float _InterTime,
	bool _Loop)
{
	GameEngineImage* FindImage = GameEngineImageManager::GetInst()->Find(_Image);
	if (nullptr == FindImage)
	{
		MsgBoxAssertString(_Name + "�������� �ʴ� �̹����� �ִϸ��̼��� ������� �߽��ϴ�.");
		return;
	}

	if (Animations_.end() != Animations_.find(_Name))
	{
		MsgBoxAssert("�̹� �����ϴ� �ִϸ��̼��� �� ������� �߽��ϴ�.");
		return;
	}

	FrameAnimation& NewAnimation = Animations_[_Name];

	NewAnimation.SetName(_Name);
	NewAnimation.TimeKey = 0;
	NewAnimation.Renderer_ = this;
	NewAnimation.Image_ = FindImage;
	NewAnimation.CurrentFrame_ = _StartIndex;
	NewAnimation.StartFrame_ = _StartIndex;
	NewAnimation.EndFrame_ = _EndIndex;
	NewAnimation.CurrentInterTime_ = _InterTime;
	NewAnimation.InterTime_ = _InterTime;
	NewAnimation.Loop_ = _Loop;

}

void GameEngineRenderer::CreateFolderAnimation(const std::string& _Image, const std::string& _Name, int _StartIndex, int _EndIndex, float _InterTime, bool _Loop /*= true*/)
{
	GameEngineFolderImage* FindImage = GameEngineImageManager::GetInst()->FolderImageFind(_Image);
	if (nullptr == FindImage)
	{
		MsgBoxAssertString(_Name + "�������� �ʴ� �̹����� �ִϸ��̼��� ������� �߽��ϴ�.");
		return;
	}

	if (Animations_.end() != Animations_.find(_Name))
	{
		MsgBoxAssert("�̹� �����ϴ� �ִϸ��̼��� �� ������� �߽��ϴ�.");
		return;
	}

	FrameAnimation& NewAnimation = Animations_[_Name];

	NewAnimation.SetName(_Name);
	NewAnimation.TimeKey = 0;
	NewAnimation.Renderer_ = this;
	NewAnimation.FolderImage_ = FindImage;
	NewAnimation.CurrentFrame_ = _StartIndex;
	NewAnimation.StartFrame_ = _StartIndex;
	NewAnimation.EndFrame_ = _EndIndex;
	NewAnimation.CurrentInterTime_ = _InterTime;
	NewAnimation.InterTime_ = _InterTime;
	NewAnimation.Loop_ = _Loop;

}

void GameEngineRenderer::CreateFolderAnimationTimeKey(const std::string& _Image, const std::string& _Name, int _TimeScaleKey, int _StartIndex, int _EndIndex, float _InterTime, bool _Loop /*= true*/)
{
	GameEngineImage* FindImage = GameEngineImageManager::GetInst()->Find(_Image);
	if (nullptr == FindImage)
	{
		MsgBoxAssertString(_Name + "�������� �ʴ� �̹����� �ִϸ��̼��� ������� �߽��ϴ�.");
		return;
	}

	if (Animations_.end() != Animations_.find(_Name))
	{
		MsgBoxAssert("�̹� �����ϴ� �ִϸ��̼��� �� ������� �߽��ϴ�.");
		return;
	}

	FrameAnimation& NewAnimation = Animations_[_Name];

	NewAnimation.SetName(_Name);
	NewAnimation.Renderer_ = this;
	NewAnimation.TimeKey = _TimeScaleKey;
	NewAnimation.Image_ = FindImage;
	NewAnimation.CurrentFrame_ = _StartIndex;
	NewAnimation.StartFrame_ = _StartIndex;
	NewAnimation.EndFrame_ = _EndIndex;
	NewAnimation.CurrentInterTime_ = _InterTime;
	NewAnimation.InterTime_ = _InterTime;
	NewAnimation.Loop_ = _Loop;
}

void GameEngineRenderer::ChangeAnimation(const std::string& _Name)
{
	std::map<std::string, FrameAnimation>::iterator FindIter = Animations_.find(_Name);

	if (Animations_.end() == FindIter)
	{
		MsgBoxAssert("�������� �ʴ� �ִϸ��̼����� ü���� �Ϸ��� �߽��ϴ�.");
		return;
	}

	if (nullptr != CurrentAnimation_
		&& CurrentAnimation_->GetNameConstPtr() == _Name)
	{
		return;
	}

	CurrentAnimation_ = &FindIter->second;	//FrameAnimation�� �����̴�.

	if (nullptr != CurrentAnimation_)
	{
		CurrentAnimation_->Reset();
	}

}

void GameEngineRenderer::FrameAnimation::Update()
{
	IsEnd = false;
	if (false == Renderer_->Pause_)
	{
		CurrentInterTime_ -= GameEngineTime::GetInst()->GetDeltaTime(TimeKey);
		if (0 >= CurrentInterTime_)
		{
			CurrentInterTime_ = InterTime_;
			++CurrentFrame_;

			if (EndFrame_ < CurrentFrame_)
			{
				if (true == Loop_)
				{
					IsEnd = true;
					CurrentFrame_ = StartFrame_;	// Loop�� True��� �̹����� �ݺ���Ų��.
				}
				else
				{
					IsEnd = true;
					CurrentFrame_ = EndFrame_;		// Loop�� false��� �ִϸ��̼� ������ EndFrame���� ������Ų��.
				}
			}
		}
	}


	if (nullptr != Image_)
	{
		Renderer_->Image_ = Image_;		// ���������� �� �ִϸ��̼� ���鶧 �����߶� �̹����� �������ش�.
		if (Renderer_->ScaleMode_ == RenderScaleMode::User)
		{
			Renderer_->SetIndex(CurrentFrame_, Renderer_->RenderScale_);
		}
		else {
			Renderer_->SetIndex(CurrentFrame_);	// ���������� �ε����� �������ش�. ��, �ش� �ִϸ��̼� �̹����� ���° ĭ(Index) �������ָ� �������� �˾Ƽ� ����Ѵ�.
		}
	}
	else if(nullptr != FolderImage_)
	{
		Renderer_->Image_ = FolderImage_->GetImage(CurrentFrame_);		// ���������� �� �ִϸ��̼� ���鶧 �����߶� �̹����� �������ش�.
		Renderer_->SetImageScale();	// ���������� �ε����� �������ش�. ��, �ش� �ִϸ��̼� �̹����� ���° ĭ(Index) �������ָ� �������� �˾Ƽ� ����Ѵ�.
	}
}


void GameEngineRenderer::SetOrder(int _Order)
{
	if (nullptr == GetActor())
	{
		MsgBoxAssert("���Ͱ� �������� �ʽ��ϴ�.");
	}

	if (nullptr == GetActor()->GetLevel())
	{
		MsgBoxAssert("������ ���õ��� �ʾҽ��ϴ�.");
	}

	if (_Order == GetOrder())
	{
		return;
	}

	GetActor()->GetLevel()->ChangeRenderOrder(this, _Order);
}

bool GameEngineRenderer::IsEndAnimation() 
{
	return CurrentAnimation_->IsEnd;
}

bool GameEngineRenderer::IsAnimationName(const std::string& _Name)
{
	return CurrentAnimation_->GetNameConstRef() == _Name;
}

const GameEngineRenderer::FrameAnimation* GameEngineRenderer::FindAnimation(const std::string& _Name)
{
	std::map<std::string, FrameAnimation>::iterator FindIter = Animations_.find(_Name);

	if (Animations_.end() == FindIter)
	{
		return nullptr;
	}

	return &FindIter->second;
}