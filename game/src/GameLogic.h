#pragma once
#include "raylib.h"
#include "Player.h"
#include "Land.h"

enum GameState
{
	PlayerHit,
	Over,
	InPlay,
	Pause,
	HighScores,
	MainMenu
};

class GameLogic
{

public:
	GameLogic();
	virtual ~GameLogic();

	void SetCamera(Camera* camera);
	bool Initialize();
	void Load();
	bool BeginRun();

	virtual void Input();
	virtual void Update(float deltaTime);
	virtual void Draw3D();
	virtual void Draw2D();

private:
	Player* ThePlayer;
	Land* TheLand;
	Camera* TheCamera = { 0 };
};

