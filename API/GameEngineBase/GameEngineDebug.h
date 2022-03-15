#pragma once
#include <crtdbg.h>
#include <assert.h>
#include <Windows.h>

// Ό³Έν :
class GameEngineDebug
{
public:
	static void LeakCheckOn();

protected:

private:
	// constrcuter destructer
	GameEngineDebug();
	~GameEngineDebug();

	// delete Function
	GameEngineDebug(const GameEngineDebug& _Other) = delete;
	GameEngineDebug(GameEngineDebug&& _Other) noexcept = delete;
	GameEngineDebug& operator=(const GameEngineDebug& _Other) = delete;
	GameEngineDebug& operator=(GameEngineDebug&& _Other) noexcept = delete;

};

#define MsgBoxAssert(Text)  MessageBeep(0); \
MessageBoxA(nullptr, Text, "Error", MB_OK); \
assert(false);

