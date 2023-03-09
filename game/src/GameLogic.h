#pragma once
#include "raylib.h"
#include "Player.h"
#include "Land.h"
#include "LanderMutantControl.h"
#include "BomberControl.h"

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

	bool Initialize();
	void SetCamera(Camera* camera);
	void Load();
	bool BeginRun();

	virtual void Input();
	virtual void Update(float deltaTime);
	virtual void Draw3D();
	virtual void Draw2D();

private:
	bool Pause = false;
	Camera* TheCamera = nullptr;
	Player* ThePlayer = new Player();
	Land* TheLand = new Land();
	LanderMutantControl* ControlLanderMutant = new LanderMutantControl();
	BomberControl* Bombers = new BomberControl();
};

