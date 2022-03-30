#include "GameEngineImage.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineWindow.h>

GameEngineImage::GameEngineImage() 
    : ImageDC_(nullptr)
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
        MsgBoxAssertString(_Path + " 경로의 이미지 로드에 실패하였습니다");
    }

    ImageDC_ = CreateCompatibleDC(nullptr);

    if (nullptr == ImageDC_)
    {
        MsgBoxAssert("ImageDC 생성에 실패했습니다.");
    }

    OldBitMap_ = (HBITMAP)SelectObject(ImageDC_, BitMap_);

    ImageScaleCheck();

    return true;
}

void GameEngineImage::BitCopy(GameEngineImage* _Other)
{
    BitCopy(_Other, { 0, 0 }, { 0, 0 }, _Other->GetScale());
}

void GameEngineImage::BitCopy(GameEngineImage* _Other, const float4& _CopyPos)
{
    BitCopy(_Other, _CopyPos, float4{ 0, 0 }, _Other->GetScale());
}

// 이미지 중앙 피벗으로 하여 복사
void GameEngineImage::BitCopyCenter(GameEngineImage* _Other, const float4& _CopyPos)
{
    BitCopy(_Other, _CopyPos - _Other->GetScale().Half(), float4{ 0, 0 }, _Other->GetScale());
}

void GameEngineImage::BitCopyCenterPivot(GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyPivot)
{
    BitCopy(_Other, _CopyPos - _Other->GetScale().Half() + _CopyPivot, float4{ 0, 0 }, _Other->GetScale());
}

// 이미지 중하단 피벗으로 하여 복사
void GameEngineImage::BitCopyBot(GameEngineImage* _Other, const float4& _CopyPos)
{
    float4 ImagePivot = _Other->GetScale().Half();
    ImagePivot.y = _Other->GetScale().y;

    BitCopy(_Other, _CopyPos - ImagePivot, float4{ 0, 0 }, _Other->GetScale());
}

void GameEngineImage::BitCopyBotPivot(GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyPivot)
{
    float4 ImagePivot = _Other->GetScale().Half();
    ImagePivot.y = _Other->GetScale().y;

    BitCopy(_Other, _CopyPos - ImagePivot + _CopyPivot, float4{ 0, 0 }, _Other->GetScale());
}

void GameEngineImage::BitCopy(GameEngineImage* _Other, const float4& _CopyPos, const float4& _OtherPivot, const float4& _OtherPivotScale)
{
    // 현제 윈도우(ImageDC)에 백버퍼(_Other)를 복사해주는 윈도우 함수
    BitBlt(
        ImageDC_,               // 이 변수에 붙여넣기함
        _CopyPos.ix(),          // 복사된 이미지 붙여넣을 위치 x
        _CopyPos.iy(),          // 복사된 이미지 붙여넣을 위치 y
        _OtherPivotScale.ix(),  // 복사된 이미지 붙여넣을 크기 x
        _OtherPivotScale.iy(),  // 복사된 이미지 붙여넣을 크기 y
        _Other->ImageDC_,       // 복사하려는 변수
        _OtherPivot.ix(),       // 복사할 변수 시작점 x
        _OtherPivot.iy(),       // 복사할 변수 시작점 y
        SRCCOPY                 // 복사하라는 명령
    );
}

void GameEngineImage::TransCopy(GameEngineImage* _Other, const float4& _CopyPos,
    const float4& _CopyScale,
    const float4& _OtherPivot, const float4& _OtherScale, unsigned int _TransColor)
{
    // 특정 색 투명
    TransparentBlt(
        ImageDC_,           
        _CopyPos.ix(),      // 복사된 이미지 붙여넣을 위치 x
        _CopyPos.iy(),      
        _CopyScale.ix(),    // 복사된 이미지 붙여넣을 크기
        _CopyScale.iy(),    
        _Other->ImageDC_,   
        _OtherPivot.ix(),   // 복사할 이미지 시작점
        _OtherPivot.iy(),   
        _OtherScale.ix(),   // 복사할 이미지 크기
        _OtherScale.iy(),   
        _TransColor         
    );
}

void GameEngineImage::Cut(const float4& _CutSize)
{
    if (0 != (GetScale().ix() % _CutSize.ix()))
    {
        MsgBoxAssert("자를수 있는 수치가 딱 맞아떨어지지 않습니다");
    }

    if (0 != (GetScale().iy() % _CutSize.iy()))
    {
        MsgBoxAssert("자를수 있는 수치가 딱 맞아떨어지지 않습니다");
    }

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

void GameEngineImage::CutCount(int _x, int _y)
{
    float4 Scale = { GetScale().x / _x, GetScale().y / _y };
    Cut(Scale);
}

int GameEngineImage::GetImagePixel(int _x, int _y)
{
    return GetPixel(ImageDC_, _x, _y);
}

void GameEngineImage::ImageScaleCheck()
{
    // DC 내부에 박혀있는 BITMAP을 리턴하는 함수
    HBITMAP CurrentBitMap = (HBITMAP)GetCurrentObject(ImageDC_, OBJ_BITMAP);
    
    // Info_에 BitMap정보(bmWidth, bmHeight, ...) 저장
    GetObject(CurrentBitMap, sizeof(BITMAP), &Info_);
}

