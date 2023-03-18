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
	bool Pause = false;
	bool NewWave = false;
	Camera* TheCamera = nullptr;
	Player* ThePlayer = new Player();
	Land* TheLand = new Land();
	Timer* NewWaveTimer = new Timer();
	ScoreKeeper* Score = new ScoreKeeper();
	SharedData* Data = new SharedData();
	LanderMutantControl* ControlLanderMutant = new LanderMutantControl();
	BomberControl* Bombers = new BomberControl();
	SwarmerControl* Swarmers = new SwarmerControl();

	void CheckEndOfWave();
};

