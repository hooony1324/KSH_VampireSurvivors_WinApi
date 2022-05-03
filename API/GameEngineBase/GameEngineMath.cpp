#include "GameEngineMath.h"


const float GameEngineMath::PIE = 3.141592653589793238462643383279502884197169399375105820974944f;
const float GameEngineMath::PIE2 = PIE * 2.0f;
const float GameEngineMath::DEG = 180.0f;

// 180을 3.14로 바꾸는건 

//                                           3.14 / 180.0f
const float GameEngineMath::DegreeToRadian = PIE / DEG;
//                                    3.14 * 180 / 3.14 
const float GameEngineMath::RadianToDegree = DEG / PIE;

GameEngineMath::GameEngineMath()
{
}

GameEngineMath::~GameEngineMath()
{
}

float4 float4::LEFT = { -1.0f, 0.0f, 0.0f, 1.0f };
float4 float4::RIGHT = { 1.0f, 0.0f, 0.0f, 1.0f };;
float4 float4::UP = { 0.0f, -1.0f, 0.0f, 1.0f };;
float4 float4::DOWN = { 0.0f, 1.0f, 0.0f, 1.0f };;
float4 float4::ZERO = { 0.0f, 0.0f, 0.0f, 0.0f };;

