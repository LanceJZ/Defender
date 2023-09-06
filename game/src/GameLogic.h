#pragma once
#include "raylib.h"
#include "ContentManager.h"
#include "Player.h"
#include "Land.h"
#include "LanderMutantControl.h"
#include "BomberControl.h"
#include "PodSwarmerControl.h"
#include "BaiterControl.h"
#include "ScoreKeeper.h"
#include "SharedData.h"
#include "ExplosionControl.h"

enum GameState
{
	PlayerHitByEnemy,
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
	//Model LoadModelWithTexture(std::string modelFileName);
	//Model SetTextureToModel(Model model, Texture2D texture);
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
	ContentManager Content;
	ScoreKeeper Score;
	SharedData Data;
	ExplosionControl Explosions;
	LanderMutantControl LandersMutants;
	BomberControl Bombers;
	PodSwarmerControl PodsSwarmers;
	BaiterControl Baiters;

	void UpdatePlayerLand(float deltaTime);
	void CheckEndOfLevelWave();
	void NewWaveStart();
	void PlayerWasHit();
	void ResetAfterExplode();
	void SmartBombFired();
	void PlayerHit();
	void NewGame();
};

