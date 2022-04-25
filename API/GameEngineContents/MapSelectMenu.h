#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class GameEngineRenderer;
class MapSelectMenu : public GameEngineActor
{
public:
	// constrcuter destructer
	MapSelectMenu();
	~MapSelectMenu();

	// delete Function
	MapSelectMenu(const MapSelectMenu& _Other) = delete;
	MapSelectMenu(MapSelectMenu&& _Other) noexcept = delete;
	MapSelectMenu& operator=(const MapSelectMenu& _Other) = delete;
	MapSelectMenu& operator=(MapSelectMenu&& _Other) noexcept = delete;

protected:

	void Start() override;
	void Update() override;
	void Render() override;

private:

};

