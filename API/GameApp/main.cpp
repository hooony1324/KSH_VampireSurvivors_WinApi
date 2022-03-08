#include <Windows.h>

#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDebug.h>

void GameLoop()
{
    Rectangle(GameEngineWindow::GETDC(), 100, 100, 200, 200);
}

int APIENTRY WinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    GameEngineDebug::LeakCheckOn();
    
    GameEngineWindow::GetInst().CreateGameWindow(hInstance, "Vampire Survivors");
    GameEngineWindow::GetInst().ShowGameWindow();
    GameEngineWindow::GetInst().MessageLoop(GameLoop);
    
    GameEngineWindow::Destroy();
} 