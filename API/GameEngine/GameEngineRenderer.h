#pragma once
#include "GameEngineEnum.h"
#include "GameEngineActorSubObject.h"

// 설명 :
class GameEngineImage;
class GameEngineRenderer : public GameEngineActorSubObject
{
	friend GameEngineActor;

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

	inline void SetType(const RenderPivot& _Type)
	{
		PivotType_ = _Type;
	}

	inline void SetScaleMode(const RenderScaleMode& _Mode)
	{
		ScaleMode_ = _Mode;
	}

	void SetImageScale();

	// 그리는 크기만 바꾸는 함수
	inline void SetScale(const float4& _Scale)
	{
		ScaleMode_ = RenderScaleMode::User;
		RenderScale_ = _Scale;
	}

	void SetImage(const std::string& _Name);

	void SetIndex(size_t _Index);

protected:
	void Render();

private:
	GameEngineImage* Image_;
	RenderPivot PivotType_;
	RenderScaleMode ScaleMode_;
	float4 RenderPivot_;
	float4 RenderScale_;
	float4 RenderImageScale_;
	float4 RenderImagePivot_;
	unsigned int TransColor_;

	// 내가 추가함
public:
	GameEngineImage& GetImage()
	{
		return *Image_;
	}

	float4 GetPivot()
	{
		return RenderPivot_;
	}

	float4 GetScale()
	{
		return RenderScale_;
	}
};