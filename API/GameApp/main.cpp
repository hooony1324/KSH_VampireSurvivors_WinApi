#include <Windows.h>
#include <GameEngineBase/GameEngineWindow.h>

int APIENTRY WinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    GameEngineWindow::GetInst().CreateGameWindow(hInstance);
    GameEngineWindow::GetInst().ShowGameWindow();

} 