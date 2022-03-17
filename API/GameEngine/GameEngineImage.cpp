#include "GameEngineImage.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineWindow.h>

GameEngineImage::GameEngineImage() 
{
}

GameEngineImage::~GameEngineImage() 
{
}

bool GameEngineImage::Create(float4 _Scale)
{
    if (true == _Scale.IsZero2D())
    {
        MsgBoxAssert("ũ�Ⱑ 0�� �̹��� ������ �õ��Ͽ����ϴ�");
        return false;
    }

    BitMap_ = CreateCompatibleBitmap(GameEngineWindow::GetHDC(), _Scale.ix(), _Scale.iy());

    ImageDC_ = CreateCompatibleDC(nullptr);

    if (nullptr == ImageDC_)
    {
        MsgBoxAssert("ImageDC ������ �����Ͽ����ϴ�");
    }

    OldBitMap_ = (HBITMAP)SelectObject(ImageDC_, BitMap_);

    ImageScaleCheck();

    return true;
}

void GameEngineImage::ImageScaleCheck()
{
    GetObject(BitMap_, sizeof(BITMAP), &Info_);
}

