#pragma once
#include "raylib.h"
#include "Player.h"
#include "Land.h"
#include "LanderMutantControl.h"
#include "BomberControl.h"
#include "SwarmerControl.h"
#include "ScoreKeeper.h"
#include "SharedData.h"

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
	Model LoadModelwithTexture(string modelFileName);
	Model UploadTextureToModel(Model model, Texture2D texture);
	void Load();
	bool BeginRun(Camera* camera);


	virtual void Input();
	virtual void Update(float deltaTime);
	virtual void Draw3D();
	virtual void Draw2D();

private:
	bool NewWave = false;

	GameState State = InPlay;
	Camera* TheCamera = nullptr;
	Player ThePlayer;
	Land TheLand;
	Timer NewWaveTimer;
	Timer PlayerResetTimer;
	ScoreKeeper Score;
	SharedData Data;
	LanderMutantControl ControlLanderMutant;
	BomberControl Bombers;
	SwarmerControl Swarmers;

	void CheckEndOfWave();
	void PlayerWasHit();
};

