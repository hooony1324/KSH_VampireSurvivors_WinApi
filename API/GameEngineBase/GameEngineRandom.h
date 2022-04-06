#pragma once
#include <random>

// 설명 :
class GameEngineRandom
{
	// 제네레이터
	// 메르헨 트위스터의 알고리즘으로 비트를 뒤섞는 녀석.
	//std::mt19937_64 mt_;

	//std::uniform_int_distribution<int> Uniform;

public:
	// constrcuter destructer
	GameEngineRandom();
	~GameEngineRandom();

	// delete Function
	GameEngineRandom(const GameEngineRandom& _Other) = delete;
	GameEngineRandom(GameEngineRandom&& _Other) noexcept = delete;
	GameEngineRandom& operator=(const GameEngineRandom& _Other) = delete;
	GameEngineRandom& operator=(GameEngineRandom&& _Other) noexcept = delete;

protected:

private:

};

