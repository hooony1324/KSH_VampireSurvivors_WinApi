#pragma once
#include <GameEngineBase/GameEngineDebug.h>
#include <map>
#include <string>

// 설명 :
class GameEngineLevel;
class GameEngineImage;
class GameEngine
{
public:
	// constrcuter destructer
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
	
	// template이유, 엔진단계는 게임단계의 내용을 알면 안된다
	template<typename GameType>
	static void Start()
	{
		GameEngineDebug::LeakCheckOn();

		GameType UserGame;			// == VampireSurvivorGame UserGame;
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

protected:
	template<typename LevelType>
	void CreateLevel(const std::string& _Name)
	{
		// LevelType => TitleLevel, PlayLevel, EndLevel...
		// LevelType에서(Title, Play, End, ...) firend GameEngine을 각각 선언하기에 불편
		// Contents레벨보다 이전 단계에서 처리해줄 필요가 있음
		LevelType* NewLevel = new LevelType();
		NewLevel->SetName(_Name);

		// 그래서 부모 클래스로 업캐스팅을 하고 부모에 friend선언을 해주면 protected매서드 접근 용이
 		GameEngineLevel* Level = NewLevel;		
		Level->Loading();
		AllLevel_.insert(std::make_pair(_Name, NewLevel));
	}

private:
	static std::map<std::string, GameEngineLevel*> AllLevel_;
	static GameEngineLevel* CurrentLevel_;
	static GameEngineLevel* NextLevel_;
	static GameEngine* UserContents_;

	// WindowMainImage_ 현재 윈도우의 HDC를 받아옴
	static GameEngineImage* WindowMainImage_;	// 화면에 나오는 이미지 버퍼
	static GameEngineImage* BackBufferImage_;	// 깜빡임 해결용 이미지 버퍼

	static void WindowCreate();
	static void EngineInit();
	static void EngineLoop();
	static void EngineEnd();

};

