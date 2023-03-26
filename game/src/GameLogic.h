#pragma once
#include "raylib.h"
#include "Player.h"
#include "Land.h"
#include "LanderMutantControl.h"
#include "BomberControl.h"
#include "SwarmerControl.h"
#include "ScoreKeeper.h"
#include "SharedData.h"
#include "ExplosionControl.h"

enum GameState
{
	PlayerHit,
	AfterPlayerHit,
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


	void Input();
	void Update(float deltaTime);
	void Draw3D();
	void Draw2D();

private:
	GameState State = MainMenu;
	Player ThePlayer;
	Land TheLand;
	Timer NewWaveTimer;
	Timer PlayerDeathTimer;
	Timer PlayerResetTimer;
	Timer WaveStartTimer;
	ScoreKeeper Score;
	SharedData Data;
	ExplosionControl Explosions;

	LanderMutantControl ControlLanderMutant;

	BomberControl Bombers;
	SwarmerControl Swarmers;

	void UpdatePlayerLand(float deltaTime);
	void CheckEndOfWave();
	void PlayerWasHit();
	void ResetAfterExplode();
};

