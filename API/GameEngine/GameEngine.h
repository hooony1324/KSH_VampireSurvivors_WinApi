#pragma once
#include <map>
#include <string>
#include <GameEngineBase/GameEngineDebug.h>

// 설명 : 게임엔진이란 게임 그자체의 시작점과 끝점 실행중을 담당
class GameEngineImage;
class GameEngineLevel;
class GameEngine
{
public:
	GameEngine();
	~GameEngine();

	// delete Function
	GameEngine(const GameEngine& _Other) = delete;
	GameEngine(GameEngine&& _Other) noexcept = delete;
	GameEngine& operator=(const GameEngine& _Other) = delete;
	GameEngine& operator=(GameEngine&& _Other) noexcept = delete;

	static inline GameEngineImage* BackBufferImage()
	{
		return BackBufferImage_;
	}

	static HDC BackBufferDC();

	virtual void GameInit() = 0;
	virtual void GameLoop() = 0;
	virtual void GameEnd() = 0;

	template<typename GameType>
	static void Start()
	{
		GameEngineDebug::LeakCheckOn();

		GameType UserGame;
		UserContents_ = &UserGame;

		WindowCreate();
		EngineEnd();
	}

	static GameEngine& GetInst()
	{
		if (nullptr == UserContents_)
		{
			MsgBoxAssert("GEngine ERROR Engine Is Not Start ");
		}

		return *UserContents_;
	}

	void ChangeLevel(const std::string& _Name);

	static inline GameEngineLevel* GetPrevLevel() 
	{
		return PrevLevel_;
	}

protected:
	template<typename LevelType>
	void CreateLevel(const std::string& _Name)
	{
		LevelType* NewLevel = new LevelType();
		NewLevel->SetName(_Name);
		GameEngineLevel* Level = NewLevel;
		Level->Loading();
		AllLevel_.insert(std::make_pair(_Name, NewLevel));
	}


private:
	static std::map<std::string, GameEngineLevel*> AllLevel_;
	static GameEngineLevel* CurrentLevel_;
	static GameEngineLevel* NextLevel_;
	static GameEngineLevel* PrevLevel_;
	static GameEngine* UserContents_;

	static GameEngineImage* WindowMainImage_; // 그려지면 화면에 진짜 나오게 되는 이미지
	static GameEngineImage* BackBufferImage_; // 깜빡임을 해결하려고 버퍼로 사용하는 이미지

	static void WindowCreate();
	static void EngineInit();
	static void EngineLoop();
	static void EngineEnd();


};

