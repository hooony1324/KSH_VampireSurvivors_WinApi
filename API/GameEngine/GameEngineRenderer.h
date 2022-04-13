#pragma once
#include "GameEngineActorSubObject.h"
#include "GameEngineEnum.h"
#include <map>


// 설명 : 
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

	// 렌더러 스케일과 이미지 스케일을 같이 맞춰줌, SetImage()에서 호출하여 사용한다.

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
	// EngineImage의 TransCopy 로 이미지를 백버퍼에 그린다.
	void Render();

private:
	friend class FrameAnimation;

	GameEngineImage* Image_;
	RenderPivot PivotType_;		// 센터 bot 등, 이미지 어느곳을 중심으로 출력할것인가
	RenderScaleMode ScaleMode_;	// ENUM(Image, User), 엔진이 정의해준 기본값으로 쓸것인가, 프로그래머가 정의한 USER값으로 쓸것인가.

	// 화면에서 출력할 좌표와 크기
	float4 RenderPivot_;		// 그려질 DC의 시작점
	float4 RenderScale_;		// 어느 크기로 그릴것인가.

	// 이미지에서 잘라낼 좌표와 크기
	float4 RenderImagePivot_;	// 복사받으려는 이미지 시작 좌표
	float4 RenderImageScale_;	// 복사받으려는 이미지 한칸의 크기

	unsigned int TransColor_;	// TransParents 에서 쓸 제외할 RGB 값
	unsigned int Alpha_;


	bool IsCameraEffect_;		// 해당 렌더러가 카메라의 영향을 받는가 안받는가, EX) UI 는 카메라의 영향을 안받는다.
	bool Pause_;


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
			: Image_(nullptr),
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

		// 처음 재생상태로 만드는것.
		void Reset()
		{
			IsEnd = false;
			CurrentFrame_ = StartFrame_;
			CurrentInterTime_ = InterTime_;

		}
	};

public:
	// 애니메이션을 만든다.
	void CreateAnimation(const std::string& _Image, const std::string& _Name, int _StartIndex, int _EndIndex, float _InterTime, bool _Loop = true);

	void CreateFolderAnimation(const std::string& _Image, const std::string& _Name, int _StartIndex, int _EndIndex, float _InterTime, bool _Loop = true);

	void CreateFolderAnimationTimeKey(const std::string& _Image, const std::string& _Name, int _TimeScaleKey, int _StartIndex, int _EndIndex, float _InterTime, bool _Loop = true);

	// 애니메이션을 재생한다.
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

