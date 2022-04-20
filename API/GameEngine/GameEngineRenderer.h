#pragma once
#include "GameEngineActorSubObject.h"
#include "GameEngineEnum.h"
#include <map>


// ���� : 
class GameEngineImage;
class GameEngineFolderImage;
class GameEngineRenderer : public GameEngineActorSubObject
{
	friend GameEngineActor;
	friend GameEngineLevel;

public:
	// constrcuter destructer
	GameEngineRenderer();
	~GameEngineRenderer();

	// delete Function
	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator=(GameEngineRenderer&& _Other) noexcept = delete;

	inline void SetTransColor(unsigned int _Color)
	{
		TransColor_ = _Color;
	}

	inline void SetPivot(const float4& _Pos)
	{
		RenderPivot_ = _Pos;
	}

	inline float4 GetPivot()
	{
		return RenderPivot_;
	}

	inline void SetPivotType(const RenderPivot& _Type)
	{
		PivotType_ = _Type;
	}

	inline void SetScaleMode(const RenderScaleMode& _Mode)
	{
		ScaleMode_ = _Mode;
	}

	// ������ �����ϰ� �̹��� �������� ���� ������, SetImage()���� ȣ���Ͽ� ����Ѵ�.

	inline void SetScale(const float4& _Scale)
	{
		ScaleMode_ = RenderScaleMode::User;
		RenderScale_ = _Scale;
	}

	inline float4 GetScale()
	{
		return RenderScale_;
	}

	inline float4 GetImagePivot()
	{
		return RenderImagePivot_;
	}

	inline float4 GetImageScale()
	{
		return RenderImageScale_;
	}

	inline GameEngineImage* GetImage()
	{
		return Image_;
	}

	inline void SetAlpha(unsigned int _Alpha)
	{
		Alpha_ = _Alpha;

		if (Alpha_ >= 255)
		{
			Alpha_ = 255;
		}
	}

	void CameraEffectOff()
	{
		IsCameraEffect_ = false;
	}

	void CameraEffectOn()
	{
		IsCameraEffect_ = true;
	}

	void SetPause(bool _Value)
	{
		Pause_ = _Value;
	}

	void PauseOn() 
	{
		Pause_ = true;
	}

	void PauseOff()
	{
		Pause_ = false;
	}

	void PauseSwitch()
	{
		Pause_ = !Pause_;
	}

	void SetImageScale();

	void SetImage(const std::string& _Name);

	void SetIndex(size_t _Index, float4 _Scale = { -1.0f, -1.0f });

	void SetOrder(int _Order) override;


protected:
	// EngineImage�� TransCopy �� �̹����� ����ۿ� �׸���.
	void Render();

private:
	friend class FrameAnimation;

	GameEngineImage* Image_;	
	RenderPivot PivotType_;		// ���� bot ��, �̹��� ������� �߽����� ����Ұ��ΰ�
	RenderScaleMode ScaleMode_;	// ENUM(Image, User), ������ �������� �⺻������ �����ΰ�, ���α׷��Ӱ� ������ USER������ �����ΰ�.

	// ȭ�鿡�� ����� ��ǥ�� ũ��
	float4 RenderPivot_;		// �׷��� DC�� ������
	float4 RenderScale_;		// ��� ũ��� �׸����ΰ�.

	// �̹������� �߶� ��ǥ�� ũ��
	float4 RenderImagePivot_;	// ����������� �̹��� ���� ��ǥ
	float4 RenderImageScale_;	// ����������� �̹��� ��ĭ�� ũ��

	unsigned int TransColor_;	// TransParents ���� �� ������ RGB ��
	unsigned int Alpha_;
	


	bool IsCameraEffect_;		// �ش� �������� ī�޶��� ������ �޴°� �ȹ޴°�, EX) UI �� ī�޶��� ������ �ȹ޴´�.
	bool Pause_;


	/// <summary>
	/// ////////////////////////////////////////////// ȸ���� Ʈ���� �̹���
	/// </summary>

	float RotZ_;
	GameEngineImage* RotationFilterImage_;

public:
	void SetRotationFilter(const std::string& _ImageName);
	


	void SetRotationZ(float _RotZ)
	{
		RotZ_ = _RotZ;
		Alpha_ = 255;
	}

	//////////////////////////////////////////////////
	//// Animation
	//////////////////////////////////////////////////
private:
	class FrameAnimation : public GameEngineNameObject
	{
	private:
		friend GameEngineRenderer;
		//friend std::map<std::string, FrameAnimation>;
		//friend std::pair<std::string, FrameAnimation>;

		GameEngineRenderer* Renderer_;
		GameEngineImage* Image_;
		GameEngineFolderImage* FolderImage_;

		int TimeKey;
		int CurrentFrame_;
		int StartFrame_;
		int EndFrame_;
		float CurrentInterTime_;
		float InterTime_;
		bool Loop_ = false;
		bool IsEnd;

	public:
		inline int WorldCurrentFrame() const
		{
			return CurrentFrame_;
		}

		inline int WorldStartFrame() const
		{
			return StartFrame_;
		}

		inline int WorldEndFrame() const
		{
			return EndFrame_;
		}

		inline int LocalCurrentFrame() const
		{
			return StartFrame_ - CurrentFrame_;
		}


	public:
		FrameAnimation()
			:	Image_(nullptr),
			Renderer_(nullptr),
			FolderImage_(nullptr),
			TimeKey(0),
			CurrentFrame_(-1),
			StartFrame_(-1),
			EndFrame_(-1),
			CurrentInterTime_(0.1f),
			InterTime_(0.1f),
			Loop_(true),
			IsEnd(false)
		{
		}

	public:

		void Update();

		// ó�� ������·� ����°�.
		void Reset()
		{
			IsEnd = false;
			CurrentFrame_ = StartFrame_;
			CurrentInterTime_ = InterTime_;

		}
	};

public:
	// �ִϸ��̼��� �����.
	void CreateAnimation(const std::string& _Image, const std::string& _Name, int _StartIndex, int _EndIndex, float _InterTime, bool _Loop = true);

	void CreateFolderAnimation(const std::string& _Image, const std::string& _Name, int _StartIndex, int _EndIndex, float _InterTime, bool _Loop = true);

	void CreateFolderAnimationTimeKey(const std::string& _Image, const std::string& _Name, int _TimeScaleKey, int _StartIndex, int _EndIndex, float _InterTime, bool _Loop = true);

	// �ִϸ��̼��� ����Ѵ�.
	void ChangeAnimation(const std::string& _Name);

	bool IsEndAnimation();

	bool IsAnimationName(const std::string& _Name);

	const FrameAnimation* FindAnimation(const std::string& _Name);

	inline const FrameAnimation* CurrentAnimation()
	{
		return CurrentAnimation_;
	}


private:
	std::map<std::string, FrameAnimation> Animations_;
	FrameAnimation* CurrentAnimation_;

};

