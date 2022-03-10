#include <Windows.h>

#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineContents/VampireSurvivorsGame.h>

VampireSurvivorsGame vsGame;

void GameInit()
{
    vsGame.GameInit();
}

void GameLoop()
{
    vsGame.GameLoop();
}

int APIENTRY WinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    GameEngineDebug::LeakCheckOn();
    
    GameEngineWindow::GetInst().CreateGameWindow(hInstance, "Vampire Survivors");
    GameEngineWindow::GetInst().ShowGameWindow();
    GameEngineWindow::GetInst().MessageLoop(GameLoop, GameInit);
    
    GameEngineWindow::Destroy();
} 