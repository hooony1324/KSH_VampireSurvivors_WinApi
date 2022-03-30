#include "GameEngineImage.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineWindow.h>

GameEngineImage::GameEngineImage() 
    : ImageDC_(nullptr)
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
        MsgBoxAssertString(_Path + " ����� �̹��� �ε忡 �����Ͽ����ϴ�");
    }

    ImageDC_ = CreateCompatibleDC(nullptr);

    if (nullptr == ImageDC_)
    {
        MsgBoxAssert("ImageDC ������ �����߽��ϴ�.");
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

// �̹��� �߾� �ǹ����� �Ͽ� ����
void GameEngineImage::BitCopyCenter(GameEngineImage* _Other, const float4& _CopyPos)
{
    BitCopy(_Other, _CopyPos - _Other->GetScale().Half(), float4{ 0, 0 }, _Other->GetScale());
}

void GameEngineImage::BitCopyCenterPivot(GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyPivot)
{
    BitCopy(_Other, _CopyPos - _Other->GetScale().Half() + _CopyPivot, float4{ 0, 0 }, _Other->GetScale());
}

// �̹��� ���ϴ� �ǹ����� �Ͽ� ����
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
    // ���� ������(ImageDC)�� �����(_Other)�� �������ִ� ������ �Լ�
    BitBlt(
        ImageDC_,               // �� ������ �ٿ��ֱ���
        _CopyPos.ix(),          // ����� �̹��� �ٿ����� ��ġ x
        _CopyPos.iy(),          // ����� �̹��� �ٿ����� ��ġ y
        _OtherPivotScale.ix(),  // ����� �̹��� �ٿ����� ũ�� x
        _OtherPivotScale.iy(),  // ����� �̹��� �ٿ����� ũ�� y
        _Other->ImageDC_,       // �����Ϸ��� ����
        _OtherPivot.ix(),       // ������ ���� ������ x
        _OtherPivot.iy(),       // ������ ���� ������ y
        SRCCOPY                 // �����϶�� ���
    );
}

void GameEngineImage::TransCopy(GameEngineImage* _Other, const float4& _CopyPos,
    const float4& _CopyScale,
    const float4& _OtherPivot, const float4& _OtherScale, unsigned int _TransColor)
{
    // Ư�� �� ����
    TransparentBlt(
        ImageDC_,           
        _CopyPos.ix(),      // ����� �̹��� �ٿ����� ��ġ x
        _CopyPos.iy(),      
        _CopyScale.ix(),    // ����� �̹��� �ٿ����� ũ��
        _CopyScale.iy(),    
        _Other->ImageDC_,   
        _OtherPivot.ix(),   // ������ �̹��� ������
        _OtherPivot.iy(),   
        _OtherScale.ix(),   // ������ �̹��� ũ��
        _OtherScale.iy(),   
        _TransColor         
    );
}

void GameEngineImage::Cut(const float4& _CutSize)
{
    if (0 != (GetScale().ix() % _CutSize.ix()))
    {
        MsgBoxAssert("�ڸ��� �ִ� ��ġ�� �� �¾ƶ������� �ʽ��ϴ�");
    }

    if (0 != (GetScale().iy() % _CutSize.iy()))
    {
        MsgBoxAssert("�ڸ��� �ִ� ��ġ�� �� �¾ƶ������� �ʽ��ϴ�");
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
    // DC ���ο� �����ִ� BITMAP�� �����ϴ� �Լ�
    HBITMAP CurrentBitMap = (HBITMAP)GetCurrentObject(ImageDC_, OBJ_BITMAP);
    
    // Info_�� BitMap����(bmWidth, bmHeight, ...) ����
    GetObject(CurrentBitMap, sizeof(BITMAP), &Info_);
}

