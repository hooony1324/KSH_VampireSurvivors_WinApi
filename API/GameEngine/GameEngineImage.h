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
	virtual ~GameEngineImage();

	// delete Function
	GameEngineImage(const GameEngineImage& _Other) = delete;
	GameEngineImage(GameEngineImage&& _Other) noexcept = delete;
	GameEngineImage& operator=(const GameEngineImage& _Other) = delete;
	GameEngineImage& operator=(GameEngineImage&& _Other) noexcept = delete;

	bool Create(float4 _Scale);
	bool Create(HDC _DC);
	bool Load(const std::string& _Path);
	
	inline float4 GetScale()
	{
		return float4(static_cast<float>(Info_.bmWidth), static_cast<float>(Info_.bmHeight));
	}

	inline HDC ImageDC()
	{
		return ImageDC_;
	}

	void BitCopy(GameEngineImage* _Other);
	void BitCopy(GameEngineImage* _Other, const float4& _CopyPos);
	void BitCopyCenter(GameEngineImage* _Other, const float4& _CopyPos);
	void BitCopyCenterPivot(GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyPivot);
	void BitCopyBot(GameEngineImage* _Other, const float4& _CopyPos);
	void BitCopyBotPivot(GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyPivot);
	void BitCopy(GameEngineImage* _Other, const float4& _CopyPos, 
		const float4& _OtherPivot, const float4& _OtherPivotScale);

	void TransCopyCenterScale(GameEngineImage* _Other, const float4& _CopyPos, const float4& _RenderScale, unsigned int _TransColor);
	void TransCopyCenter(GameEngineImage* _Other, const float4& _CopyPos, unsigned int _TransColor);

	void TransCopy(GameEngineImage* _Other, const float4& _CopyPos,
		const float4& _CopyScale,
		const float4& _OtherPivot, const float4& _OtherScale, unsigned int _TransColor);

protected:

private:
	HDC ImageDC_;
	HBITMAP BitMap_;	
	HBITMAP OldBitMap_;
	BITMAP Info_;			// 현재 비트맵의 사이즈

	void ImageScaleCheck();
};

