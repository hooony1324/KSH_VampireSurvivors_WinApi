#include "GameEngineDirectory.h"
#include "GameEngineDebug.h"
#include "GameEngineFile.h"
#include "GameEngineString.h"

GameEngineDirectory::GameEngineDirectory()
{
	SetCurrentPath();
}

GameEngineDirectory::~GameEngineDirectory()
{
}

void GameEngineDirectory::MoveParent()
{
	Path_ = Path_.parent_path();
}

bool GameEngineDirectory::IsRoot()
{
	return Path_ == Path_.root_directory();
}

void GameEngineDirectory::MoveParent(const std::string& _Name)
{
	while (false == IsRoot())
	{
		Path_ = Path_.parent_path();

		if (GetFileName() == _Name)
		{
			break;
		}
	}
}

void GameEngineDirectory::Move(const std::string& _Name)
{
	std::filesystem::path CheckPath = Path_;

	CheckPath.append(_Name);

	if (false == std::filesystem::exists(CheckPath))
	{
		MsgBoxAssertString(_Name + " Path is not exists");
		return;
	}

	Path_ = CheckPath;
}

std::vector<GameEngineFile> GameEngineDirectory::GetAllFile(const std::string& _Ext)
{
	std::filesystem::directory_iterator DirIter(Path_);

	std::string Ext = _Ext;

	if (Ext != "")
	{
		GameEngineString::ToUpper(Ext);
		if (std::string::npos == Ext.find("."))
		{
			Ext = "." + Ext;
		}
	}

	std::vector<GameEngineFile> Return;
	// 디렉토리까지 다나오니까 File
	for (const std::filesystem::directory_entry& Entry : DirIter)
	{
		if (true == Entry.is_directory())
		{
			// 이때 재귀 돌려야죠.
			continue;
		}

		if (Ext != "")
		{
			GameEnginePath NewPath = Entry.path();
			std::string OtherExt = NewPath.GetExtension();
			GameEngineString::ToUpper(OtherExt);

			if (OtherExt != Ext)
			{
				continue;
			}
		}

		Return.push_back(GameEngineFile(Entry.path()));

	}

	return Return;

}