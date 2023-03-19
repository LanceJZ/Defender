#pragma once
#include "raylib.h"
#include "GameLogic.h"
#include <vector>
using namespace std;

class Game
{
public:
	Game();
	~Game();

	bool Initialize();
	bool Load();
	bool BeginRun();
	void GameLoop();

	Camera TheCamera = { 0 };

private:
	GameLogic gameLogic;

	void ProcessInput();
	void Update(float deltaTime);
	void Draw();
	void Shutdown();
};

