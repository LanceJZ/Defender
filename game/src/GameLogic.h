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
	WaveStart,
	NewWave,
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
	GameState State = WaveStart;
	Camera* TheCamera = nullptr;
	Player ThePlayer;
	Land TheLand;
	Timer NewWaveTimer;
	Timer PlayerResetTimer;
	Timer WaveStartTimer;
	ScoreKeeper Score;
	SharedData Data;
	LanderMutantControl ControlLanderMutant;
	BomberControl Bombers;
	SwarmerControl Swarmers;

	void UpdatePlayerLand(float deltaTime);
	void CheckEndOfWave();
	void PlayerWasHit();
};

