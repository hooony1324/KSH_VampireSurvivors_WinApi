#include "GameEngineWindow.h"
#include "GameEngineDebug.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    return DefWindowProc(hWnd, message, wParam, lParam);
}

GameEngineWindow* GameEngineWindow::Inst_ = new GameEngineWindow();

GameEngineWindow::GameEngineWindow()
    : hInst_(nullptr)
    , hWnd_(nullptr)
{
}

GameEngineWindow::~GameEngineWindow() 
{
}

void GameEngineWindow::RegClass(HINSTANCE _hInst)
{
    WNDCLASSEXA wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = _hInst;
    wcex.hIcon = nullptr;
    wcex.hCursor = LoadCursor(nullptr, IDC_HAND);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = "GameEngineWindowClass";
    wcex.hIconSm = nullptr;
    RegisterClassExA(&wcex);
}

void GameEngineWindow::CreateGameWindow(HINSTANCE _hInst, const std::string& _Title)
{
    if (nullptr != hInst_)
    {
        MsgBoxAssert("�����츦 2�� ������ �߽��ϴ�.");
        return;
    }

    Title_ = _Title;
    hInst_ = _hInst;
    RegClass(hInst_);

    hWnd_ = CreateWindowExA(0L, "GameEngineWindowClass", Title_.c_str(), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, _hInst, nullptr);

    if (!hWnd_)
    {
        return;
    }
}

void GameEngineWindow::ShowGameWindow()
{
    if (nullptr == hWnd_)
    {
        MsgBoxAssert("���� �����찡 ��������� �ʾҽ��ϴ� ȭ�鿡 ����Ҽ� �����ϴ�.");
        return;
    }

    ShowWindow(hWnd_, SW_SHOW);
    UpdateWindow(hWnd_);
}

