#include <Windows.h>

#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineContents/VampireSurvivorsGame.h>
#include <GameEngine/GameEngine.h>

// 내가 추가..
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define DBG_NEW new
#endif

int APIENTRY WinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    GameEngine::Start<VampireSurvivorsGame>();
} 