#include "GameEngineImage.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineWindow.h>

GameEngineImage::GameEngineImage() 
{
}

GameEngineImage::~GameEngineImage() 
{
    // 릭으로 체크는 안되지만 지워주는게 좋다
    // 윈도우의 방식으로 윈도우 함수를 이용해서 할당해제 한다
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

// BackBuffer 생성 용
bool GameEngineImage::Create(float4 _Scale)
{
    if (true == _Scale.IsZero2D())
    {
        MsgBoxAssert("크기가 0인 이미지 생성을 시도하였습니다");
        return false;
    }

    // Bitmap 따로 생성 (HDC의 2차원 배열 내용), 이에 맞는 DC핸들 필요
    BitMap_ = CreateCompatibleBitmap(GameEngineWindow::GetHDC(), _Scale.ix(), _Scale.iy());

    // 빈 DC핸들 생성 (1 x 1 Bitmap 붙어있음)
    ImageDC_ = CreateCompatibleDC(nullptr);

    if (nullptr == ImageDC_)
    {
        MsgBoxAssert("ImageDC 생성에 실패하였습니다");
    }

    // SelectObject()는 새로운 BitMap을 받고 이전의 BitMap을 반환해줌
    OldBitMap_ = (HBITMAP)SelectObject(ImageDC_, BitMap_);

    // 현재 비트맵 정보 Info_에 저장
    ImageScaleCheck();

    return true;
}

// Window의 버퍼 받아오는 용
bool GameEngineImage::Create(HDC _DC)
{
    ImageDC_ = _DC;
    ImageScaleCheck();
    return true;
}

void GameEngineImage::BitCopy(GameEngineImage* _Other)
{
    BitCopy(_Other, { 0, 0 }, { 0, 0 }, _Other->GetScale());
}

void GameEngineImage::BitCopy(GameEngineImage* _Other, const float4& _CopyPos, const float4& _OtherPivot, const float4& _OtherPivotScale)
{
    // 현제 윈도우(ImageDC)에 백버퍼(_Other)를 복사해주는 윈도우 함수
    BitBlt(
        ImageDC_,               // 이 변수에 붙여넣기함
        _CopyPos.ix(),          // 붙여넣을 이미지 위치 x
        _CopyPos.iy(),          // 붙여넣을 이미지 위치 y
        _OtherPivotScale.ix(),  // 붙여넣을 이미지 크기 x
        _OtherPivotScale.iy(),  // 붙여넣을 이미지 크기 y
        _Other->ImageDC_,       // 복사하려는 변수
        _OtherPivot.ix(),       // 복사할 변수 시작점 x
        _OtherPivot.iy(),       // 복사할 변수 시작점 y
        SRCCOPY                 // 복사하라는 명령
    );
    
}

void GameEngineImage::ImageScaleCheck()
{
    // DC 내부에 박혀있는 BITMAP을 꺼내오는 함수
    HBITMAP CurrentBitMap = (HBITMAP)GetCurrentObject(ImageDC_, OBJ_BITMAP);

    // Info_에 BitMap정보(bmWidth, bmHeight, ...) 저장
    GetObject(BitMap_, sizeof(BITMAP), &Info_);
}

