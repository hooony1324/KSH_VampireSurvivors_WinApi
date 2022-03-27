#include "GameEngine.h"
#include <GameEngineBase/GameEngineWindow.h>
#include "GameEngineLevel.h"
#include "GameEngineImageManager.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>

std::map<std::string, GameEngineLevel*> GameEngine::AllLevel_;
GameEngineLevel* GameEngine::CurrentLevel_ = nullptr;
GameEngineLevel* GameEngine::NextLevel_ = nullptr;
GameEngine* GameEngine::UserContents_ = nullptr;
GameEngineImage* GameEngine::WindowMainImage_ = nullptr;
GameEngineImage* GameEngine::BackBufferImage_ = nullptr;

GameEngine::GameEngine() 
{
}

GameEngine::~GameEngine() 
{
}

HDC GameEngine::BackBufferDC()
{
    return BackBufferImage_->ImageDC();
}

void GameEngine::ChangeLevel(const std::string& _Name)
{
    std::map<std::string, GameEngineLevel*>::iterator FindIter = AllLevel_.find(_Name);

    if (AllLevel_.end() == FindIter)
    {
        MsgBoxAssert("Level Find Error");
        return;
    }
    NextLevel_ = FindIter->second;
}

void GameEngine::WindowCreate()
{
    GameEngineWindow::GetInst().CreateGameWindow(nullptr, "GameWindow");
    GameEngineWindow::GetInst().ShowGameWindow();
    GameEngineWindow::GetInst().MessageLoop(EngineInit, EngineLoop);
}

void GameEngine::EngineInit()
{
    UserContents_->GameInit();

    // ȭ�鿡 ������ �̹��� ���� �޾ƿ�
    WindowMainImage_ = GameEngineImageManager::GetInst()->Create("WindowMain", GameEngineWindow::GetHDC());
    // ������۸��� �̹��� ���� ����
    BackBufferImage_ = GameEngineImageManager::GetInst()->Create("BackBuffer", GameEngineWindow::GetScale());
}

void GameEngine::EngineLoop()
{
    GameEngineTime::GetInst()->Update();

    UserContents_->GameLoop();

    // Level ����(���� ���۽� ChangeLevel()�� NextLevel_�� �����Ǿ� ����)
    if (nullptr != NextLevel_)
    {
        // ���� ������ �������� SceneChangeEnd ȣ��
        if (nullptr != CurrentLevel_)
        {
            CurrentLevel_->LevelChangeEnd();
        }
        // ���� ������ �̵�
        CurrentLevel_ = NextLevel_;
        // ���� �̵��� SceneChangeStart ȣ��
        if (nullptr != CurrentLevel_)
        {
            CurrentLevel_->LevelChangeStart();
        }

        NextLevel_ = nullptr;
        GameEngineTime::GetInst()->Reset();
    }

    if (nullptr == CurrentLevel_)
    {
        MsgBoxAssert("Level is nullptr, GameEngine Loop Error!");
    }

    GameEngineInput::GetInst()->Update();

    CurrentLevel_->Update();
    CurrentLevel_->ActorUpdate();
    CurrentLevel_->ActorRender();
    WindowMainImage_->BitCopy(BackBufferImage_);

    // Death �� Actor Realease
    CurrentLevel_->ActorRelease();
}

void GameEngine::EngineEnd()
{
    UserContents_->GameEnd();

    std::map<std::string, GameEngineLevel*>::iterator StartIter = AllLevel_.begin();
    std::map<std::string, GameEngineLevel*>::iterator EndIter = AllLevel_.end();

    for (; StartIter != EndIter; ++StartIter)
    {
        if (nullptr == StartIter->second)
        {
            continue;
        }
        delete StartIter->second;
    }

    GameEngineImageManager::Destroy();
    GameEngineInput::Destroy();
    GameEngineTime::Destroy();
    GameEngineWindow::Destroy();

}

