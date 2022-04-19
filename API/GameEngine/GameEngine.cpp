#include "GameEngine.h"
#include <GameEngineBase/GameEngineWindow.h>
#include "GameEngineLevel.h"
#include "GameEngineImageManager.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineSound.h>

std::map<std::string, GameEngineLevel*> GameEngine::AllLevel_;
GameEngineLevel* GameEngine::CurrentLevel_ = nullptr;
GameEngineLevel* GameEngine::NextLevel_ = nullptr;
GameEngineLevel* GameEngine::PrevLevel_ = nullptr;

GameEngine* GameEngine::UserContents_ = nullptr;
GameEngineImage* GameEngine::BackBufferImage_ = nullptr;
GameEngineImage* GameEngine::WindowMainImage_ = nullptr; // �׷����� ȭ�鿡 ��¥ ������ �Ǵ� �̹���

HDC GameEngine::BackBufferDC()
{
    return BackBufferImage_->ImageDC();
}

GameEngine::GameEngine()
{
}

GameEngine::~GameEngine()
{

}

void GameEngine::GameInit()
{

}

void GameEngine::GameLoop()
{

}

void GameEngine::GameEnd()
{

}

void GameEngine::WindowCreate()
{
    GameEngineWindow::GetInst().CreateGameWindow(nullptr, "GameWindow");
    GameEngineWindow::GetInst().ShowGameWindow();
    GameEngineWindow::GetInst().MessageLoop(EngineInit, EngineLoop);
}

void GameEngine::EngineInit()
{
    // ���⼭ �������� ũ�Ⱑ �����ɰ� �̹Ƿ�
    UserContents_->GameInit();

    // ����۸� ����� ����.
    WindowMainImage_ = GameEngineImageManager::GetInst()->Create("WindowMain", GameEngineWindow::GetHDC());
    BackBufferImage_ = GameEngineImageManager::GetInst()->Create("BackBuffer", GameEngineWindow::GetScale());

}
void GameEngine::EngineLoop()
{
    GameEngineTime::GetInst()->Update();

    // �������ؿ��� �� �����Ӹ��� üũ�ϰ� ������
    UserContents_->GameLoop();

    // �����Լ���� �ϴµ�
    // ��� ����
    if (nullptr != NextLevel_)
    {
        PrevLevel_ = CurrentLevel_;

        if (nullptr != CurrentLevel_)
        {
            CurrentLevel_->ActorLevelChangeEnd(NextLevel_);
            CurrentLevel_->LevelChangeEnd(NextLevel_);

            CurrentLevel_->ObjectLevelMoveCheck(NextLevel_);

        }
        
        GameEngineLevel* PrevLevel = CurrentLevel_;
        CurrentLevel_ = NextLevel_;

        if (nullptr != CurrentLevel_)
        {
            CurrentLevel_->LevelChangeStart(PrevLevel);
            CurrentLevel_->ActorLevelChangeStart(PrevLevel);
        }

        NextLevel_ = nullptr;
        GameEngineTime::GetInst()->Reset();

        Rectangle(WindowMainImage_->ImageDC(), 0, 0, WindowMainImage_->GetScale().ix(), WindowMainImage_->GetScale().iy());
        Rectangle(BackBufferImage_->ImageDC(), 0, 0, BackBufferImage_->GetScale().ix(), BackBufferImage_->GetScale().iy());
    }

    if (nullptr == CurrentLevel_)
    {
        MsgBoxAssert("Level is nullptr => GameEngine Loop Error");
    }

    GameEngineSound::Update();
    GameEngineInput::GetInst()->Update(GameEngineTime::GetInst()->GetDeltaTime());

    // �������� �ð������� �ִ� �����̶��
    // �� �����Ӹ��� �ð��� üũ�ؾ��ϴµ� �׷����� 
    CurrentLevel_->Update();
    CurrentLevel_->ActorUpdate();
    CurrentLevel_->ActorRender();
    CurrentLevel_->CollisionDebugRender();
    WindowMainImage_->BitCopy(BackBufferImage_);

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


    GameEngineSound::AllResourcesDestroy();
    GameEngineImageManager::Destroy();
    GameEngineInput::Destroy();
    GameEngineTime::Destroy();
    GameEngineWindow::Destroy();
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
