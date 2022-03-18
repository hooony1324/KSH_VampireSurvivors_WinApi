#pragma once
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineMath.h>
#include <Windows.h>

// 설명 :
class GameEngineImage : public GameEngineNameObject
{
public:
	// constrcuter destructer
	GameEngineImage();
	~GameEngineImage();

	// delete Function
	GameEngineImage(const GameEngineImage& _Other) = delete;
	GameEngineImage(GameEngineImage&& _Other) noexcept = delete;
	GameEngineImage& operator=(const GameEngineImage& _Other) = delete;
	GameEngineImage& operator=(GameEngineImage&& _Other) noexcept = delete;

	bool Create(float4 _Scale);
	bool Create(HDC _DC);
	
	inline float4 GetScale()
	{
		return float4(static_cast<float>(Info_.bmWidth), static_cast<float>(Info_.bmHeight));
	}

	inline HDC ImageDC()
	{
		return ImageDC_;
	}

	void BitCopy(GameEngineImage* _Other);
	void BitCopy(GameEngineImage* _Other, const float4& _CopyPos, const float4& _OtherPivot, const float4& _OtherPivotScale);

protected:

private:
	HDC ImageDC_;
	HBITMAP BitMap_;	
	HBITMAP OldBitMap_;
	BITMAP Info_;			// 현재 비트맵의 사이즈

	void ImageScaleCheck();
};

