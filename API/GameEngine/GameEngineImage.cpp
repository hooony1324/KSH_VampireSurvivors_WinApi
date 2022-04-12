#include "GameEngineImage.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineWindow.h>

// #pragma comment(lib, "msimg32.lib")

GameEngineImage::GameEngineImage()
	:ImageDC_(nullptr)
{
}

GameEngineImage::~GameEngineImage()
{
	// Window에서 할당해 온 애들은 릭으로 체크가 안되지만 지워주는게 깔끔하다.
	// 윈도우에세 할당해왔으므로 윈도우의 함수를 이용해서 지워야한다.

	if (nullptr != BitMap_)
	{
		DeleteObject(BitMap_);
		BitMap_ = nullptr;
	}

	if (nullptr != OldBitMap_)
	{
		DeleteObject(OldBitMap_);
		OldBitMap_ = nullptr;
	}

	if (nullptr != ImageDC_)
	{
		DeleteDC(ImageDC_);
		ImageDC_ = nullptr;
	}
}

bool GameEngineImage::Create(HDC _DC)
{
	ImageDC_ = _DC;
	ImageScaleCheck();
	return true;
}

bool GameEngineImage::Create(float4 _Scale)
{
	if (true == _Scale.IsZero2D())
	{
		MsgBoxAssert("크기가 0인 이미지를 제작하려고 했습니다.");
		return false;
	}

	// 먼저 이미지 크기만한 비트맵 만들어주기
	BitMap_ = CreateCompatibleBitmap(GameEngineWindow::GetHDC(), _Scale.ix(), _Scale.iy());

	ImageDC_ = CreateCompatibleDC(nullptr);

	if (nullptr == ImageDC_)
	{
		MsgBoxAssert("ImageDc 생성에 실패했습니다.");
	}

	OldBitMap_ = (HBITMAP)SelectObject(ImageDC_, BitMap_);

	ImageScaleCheck();

	return true;
}

bool GameEngineImage::Load(const std::string& _Path)
{
	BitMap_ = static_cast<HBITMAP>(LoadImageA(
		nullptr,
		_Path.c_str(),
		IMAGE_BITMAP,
		0,
		0,
		LR_LOADFROMFILE
	));

	if (nullptr == BitMap_)
	{
		MsgBoxAssertString(_Path + " 이미지 로드에 실패했습니다. 여러분들이 살펴봐야할 문제 1. 경로는 제대로 됐나요? 2. 디버깅은 제대로 봤나요");
	}

	// 비어있지가 않음 쪼만한 DC같이 만들어줌
	ImageDC_ = CreateCompatibleDC(nullptr);

	if (nullptr == ImageDC_)
	{
		MsgBoxAssert("ImageDc 생성에 실패했습니다.");
	}

	OldBitMap_ = (HBITMAP)SelectObject(ImageDC_, BitMap_);

	ImageScaleCheck();

	return true;
}

void GameEngineImage::ImageScaleCheck()
{
	// DC 내부에 박혀있는 BITMAP을 꺼내오는 함수
	HBITMAP CurrentBitMap = (HBITMAP)GetCurrentObject(ImageDC_, OBJ_BITMAP);
	GetObject(CurrentBitMap, sizeof(BITMAP), &Info_);
}

void GameEngineImage::BitCopy(GameEngineImage* _Other, const float4& _CopyPos)
{
	BitCopy(_Other, _CopyPos, _Other->GetScale(), float4{ 0, 0 });
}

void GameEngineImage::BitCopyCenter(GameEngineImage* _Other, const float4& _CopyPos)
{
	BitCopy(_Other, _CopyPos - _Other->GetScale().Half(), _Other->GetScale(), float4{ 0, 0 });
}

void GameEngineImage::BitCopyCenterPivot(GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyPivot)
{
	BitCopy(_Other, _CopyPos - _Other->GetScale().Half() + _CopyPivot, _Other->GetScale(), float4{ 0, 0 });
}

void GameEngineImage::BitCopyBot(GameEngineImage* _Other, const float4& _CopyPos)
{
	float4 ImagePivot = _Other->GetScale().Half();
	ImagePivot.y = _Other->GetScale().y;

	BitCopy(_Other, _CopyPos - ImagePivot, _Other->GetScale(), float4{ 0, 0 });
}

void GameEngineImage::BitCopyBotPivot(GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyPivot)
{
	float4 ImagePivot = _Other->GetScale().Half();
	ImagePivot.y = _Other->GetScale().y;

	BitCopy(_Other, _CopyPos - ImagePivot + _CopyPivot, _Other->GetScale(), float4{ 0, 0 });
}

void GameEngineImage::BitCopy(GameEngineImage* _Other)
{
	BitCopy(_Other, { 0, 0 }, _Other->GetScale(), { 0, 0 });
}

// 다른 이미지가 들어와서
void GameEngineImage::BitCopy(GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyScale, const float4& _OtherPivot)
{
	// 윈도우에서 지원해주는 일반적인 dc vs dc의 복사함수입니다.
	BitBlt(
		ImageDC_, // 여기에 복사해라.
		_CopyPos.ix(), // 내 이미지의 이 부분 x
		_CopyPos.iy(), // 내 이미지의 이 부분 y 에 복사해라
		_CopyScale.ix(), // 내 이미지의 이 크기만큼 x
		_CopyScale.iy(), // 내 이미지의 이 크기만큼 y
		_Other->ImageDC_, // 복사하려는 대상은
		_OtherPivot.ix(), // 복사하려는 대상의 시작점X
		_OtherPivot.iy(),// 복사하려는 대상의 시작점Y
		SRCCOPY // 복사하라는 명령
	);
}

//////////////////////////////////////////////////////////////////////// Trans


void GameEngineImage::TransCopy(GameEngineImage* _Other, const float4& _CopyPos,
	const float4& _CopyScale,
	const float4& _OtherPivot, const float4& _OtherScale, unsigned int _TransColor)
{
	// TransCopy(_Other, _CopyPos - _RenderScale.Half(), _RenderScale, _RenderPivot, _Other->GetScale(), _TransColor);

	TransparentBlt(
		ImageDC_, // 여기에 복사(우리 윈도우이미지)
		_CopyPos.ix(), // 윈도우 이미지의 위치 x에서부터 y
		_CopyPos.iy(), // 윈도우 이미지의 위치 x에서부터 y
		_CopyScale.ix(), // 내 이미지의 이 크기만큼 x
		_CopyScale.iy(), // 내 이미지의 이 크기만큼 y
		_Other->ImageDC_, // 복사하려는 대상은(거기에 그려지는 이미지가 뭔데?커비)
		_OtherPivot.ix(), // 복사하려는 대상의 시작점X 위치
		_OtherPivot.iy(),// 복사하려는 대상의 시작점Y
		_OtherScale.ix(), // 복사하려는 대상의 시작점X 크기
		_OtherScale.iy(),// 복사하려는 대상의 시작점Y
		_TransColor // 복사하라는 명령
	);
}

void GameEngineImage::AlphaCopy(GameEngineImage* _Other, const float4& _CopyPos,
	const float4& _CopyScale,
	const float4& _OtherPivot, const float4& _OtherScale, unsigned int _Alpha)
{
	BLENDFUNCTION Func;
	Func.BlendOp = AC_SRC_OVER;
	Func.BlendFlags = 0;
	Func.SourceConstantAlpha = _Alpha;
	Func.AlphaFormat = AC_SRC_ALPHA;


	AlphaBlend(
		ImageDC_, // 여기에 복사(우리 윈도우이미지)
		_CopyPos.ix(), // 윈도우 이미지의 위치 x에서부터 y
		_CopyPos.iy(), // 윈도우 이미지의 위치 x에서부터 y
		_CopyScale.ix(), // 내 이미지의 이 크기만큼 x
		_CopyScale.iy(), // 내 이미지의 이 크기만큼 y
		_Other->ImageDC_, // 복사하려는 대상은(거기에 그려지는 이미지가 뭔데?커비)
		_OtherPivot.ix(), // 복사하려는 대상의 시작점X 위치
		_OtherPivot.iy(),// 복사하려는 대상의 시작점Y
		_OtherScale.ix(), // 복사하려는 대상의 시작점X 크기
		_OtherScale.iy(),// 복사하려는 대상의 시작점Y
		Func // 복사하라는 명령
	);

}


void GameEngineImage::CutCount(int _x, int _y)
{
	float4 Scale = { GetScale().x / _x, GetScale().y / _y };
	Cut(Scale);
}

void GameEngineImage::Cut(const float4& _CutSize)
{
	// 딱맞아 떨어지게 만들어줄것.
	if (0 != (GetScale().ix() % _CutSize.ix()))
	{
		MsgBoxAssert("자를수 있는 수치가 딱 맞아떨어지지 않습니다.");
	}

	if (0 != (GetScale().iy() % _CutSize.iy()))
	{
		MsgBoxAssert("자를수 있는 수치가 딱 맞아떨어지지 않습니다.");
	}

	// 가로세로 갯수를 구하고
	int XCount = GetScale().ix() / _CutSize.ix();
	int YCount = GetScale().iy() / _CutSize.iy();

	for (int y = 0; y < YCount; y++)
	{
		for (int x = 0; x < XCount; x++)
		{
			CutPivot_.push_back({ static_cast<float>(x * _CutSize.ix()), static_cast<float>(y * _CutSize.iy()) });
			CutScale_.push_back(_CutSize);
		}
	}

}



int GameEngineImage::GetImagePixel(int _x, int _y)
{
	return GetPixel(ImageDC_, _x, _y);
}