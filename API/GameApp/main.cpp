#include <Windows.h>

#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineContents/VampireSurvivorsGame.h>
#include <GameEngine/GameEngine.h>

int APIENTRY WinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR    lpCmdLine,
    _In_ int       nCmdShow)
{

    GameEngine::Start<VampireSurvivorsGame>();
} 