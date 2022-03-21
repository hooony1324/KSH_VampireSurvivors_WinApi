#include "GameEngineImage.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineWindow.h>

GameEngineImage::GameEngineImage() 
{
}

GameEngineImage::~GameEngineImage() 
{
    // ������ üũ�� �ȵ����� �����ִ°� ����
    // �������� ������� ������ �Լ��� �̿��ؼ� �Ҵ����� �Ѵ�
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

// BackBuffer ���� ��
bool GameEngineImage::Create(float4 _Scale)
{
    if (true == _Scale.IsZero2D())
    {
        MsgBoxAssert("ũ�Ⱑ 0�� �̹��� ������ �õ��Ͽ����ϴ�");
        return false;
    }

    // Bitmap ���� ���� (HDC�� 2���� �迭 ����), �̿� �´� DC�ڵ� �ʿ�
    BitMap_ = CreateCompatibleBitmap(GameEngineWindow::GetHDC(), _Scale.ix(), _Scale.iy());

    // �� DC�ڵ� ���� (1 x 1 Bitmap �پ�����)
    ImageDC_ = CreateCompatibleDC(nullptr);

    if (nullptr == ImageDC_)
    {
        MsgBoxAssert("ImageDC ������ �����Ͽ����ϴ�");
    }

    // SelectObject()�� ���ο� BitMap�� �ް� ������ BitMap�� ��ȯ����
    OldBitMap_ = (HBITMAP)SelectObject(ImageDC_, BitMap_);

    // ���� ��Ʈ�� ���� Info_�� ����
    ImageScaleCheck();

    return true;
}

// Window�� ���� �޾ƿ��� ��
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
    // ���� ������(ImageDC)�� �����(_Other)�� �������ִ� ������ �Լ�
    BitBlt(
        ImageDC_,               // �� ������ �ٿ��ֱ���
        _CopyPos.ix(),          // �ٿ����� �̹��� ��ġ x
        _CopyPos.iy(),          // �ٿ����� �̹��� ��ġ y
        _OtherPivotScale.ix(),  // �ٿ����� �̹��� ũ�� x
        _OtherPivotScale.iy(),  // �ٿ����� �̹��� ũ�� y
        _Other->ImageDC_,       // �����Ϸ��� ����
        _OtherPivot.ix(),       // ������ ���� ������ x
        _OtherPivot.iy(),       // ������ ���� ������ y
        SRCCOPY                 // �����϶�� ���
    );
    
}

void GameEngineImage::ImageScaleCheck()
{
    // DC ���ο� �����ִ� BITMAP�� �������� �Լ�
    HBITMAP CurrentBitMap = (HBITMAP)GetCurrentObject(ImageDC_, OBJ_BITMAP);

    // Info_�� BitMap����(bmWidth, bmHeight, ...) ����
    GetObject(BitMap_, sizeof(BITMAP), &Info_);
}

