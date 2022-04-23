#pragma once
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineMath.h>
#include <Windows.h>
#include <vector>

// Ό³Έν :
class GameEngineFont : public GameEngineNameObject
{
public:
	// constrcuter destructer
	GameEngineFont();
	~GameEngineFont();

	// delete Function
	GameEngineFont(const GameEngineFont& _Other) = delete;
	GameEngineFont(GameEngineFont&& _Other) noexcept = delete;
	GameEngineFont& operator=(const GameEngineFont& _Other) = delete;
	GameEngineFont& operator=(GameEngineFont&& _Other) noexcept = delete;

	bool Load(const std::string& _Path);
	void Draw(const std::string& _Text, float4 _Postion, float _Size, float _Weight);

protected:

	//SetTextColor(BackBufferDC_, RGB(255, 255, 255));
	//SetBkMode(BackBufferDC_, TRANSPARENT);

private:
	HFONT hFont;
	HFONT oldFont;
	std::string FontName;

};

