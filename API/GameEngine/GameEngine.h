#pragma once
#include <GameEngineBase/GameEngineDebug.h>
#include <map>
#include <string>

// ���� :
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
	
	// template����, �����ܰ�� ���Ӵܰ��� ������ �˸� �ȵȴ�
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
		// LevelType����(Title, Play, End, ...) firend GameEngine�� ���� �����ϱ⿡ ����
		// Contents�������� ���� �ܰ迡�� ó������ �ʿ䰡 ����
		LevelType* NewLevel = new LevelType();
		NewLevel->SetName(_Name);

		// �׷��� �θ� Ŭ������ ��ĳ������ �ϰ� �θ� friend������ ���ָ� protected�ż��� ���� ����
 		GameEngineLevel* Level = NewLevel;		
		Level->Loading();
		AllLevel_.insert(std::make_pair(_Name, NewLevel));
	}

private:
	static std::map<std::string, GameEngineLevel*> AllLevel_;
	static GameEngineLevel* CurrentLevel_;
	static GameEngineLevel* NextLevel_;
	static GameEngine* UserContents_;

	// WindowMainImage_ ���� �������� HDC�� �޾ƿ�
	static GameEngineImage* WindowMainImage_;	// ȭ�鿡 ������ �̹��� ����
	static GameEngineImage* BackBufferImage_;	// ������ �ذ�� �̹��� ����

	static void WindowCreate();
	static void EngineInit();
	static void EngineLoop();
	static void EngineEnd();

};

