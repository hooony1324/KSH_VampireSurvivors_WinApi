#pragma once
#include "GameEnginePath.h"

class GameEngineFile;
class GameEngineDirectory : public GameEnginePath
{
public:
	// constrcuter destructer
	GameEngineDirectory();
	GameEngineDirectory(const char* _Path);
	GameEngineDirectory(std::filesystem::path _Path);
	GameEngineDirectory(const GameEngineDirectory& _Other);
	~GameEngineDirectory();

	void MoveParent();

	void MoveParent(const std::string& _Name);

	bool IsRoot();

	void Move(const std::string& _Name);

	std::vector<GameEngineFile> GetAllFile(const std::string& _Ext = "");

	std::vector<GameEngineDirectory> GetAllDirectory();

protected:
	

private:

};

