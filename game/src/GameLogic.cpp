#include "GameLogic.h"
#include <string>
#include <raymath.h>

GameLogic::GameLogic()
{
}

GameLogic::~GameLogic()
{
}

bool GameLogic::Initialize()
{
	SetWindowTitle("Defender Alpha 01.161");
	Score.Initialize();
	ThePlayer.Initialize();
	LandersMutants.Initialize();
	TheLand.Initialize();
	Bombers.Initialize();
	PodsSwarmers.Initialize();
	Explosions.Initialize();
	NewWaveTimer.Set(1.5f);
	WaveStartTimer.Set(1.666f);

	return false;
}

Model GameLogic::LoadModelwithTexture(std::string modelFileName)
{
	std::string path = "models/";

	std::string namePNG = path;
	namePNG.append(modelFileName);
	namePNG.append(".png");

	std::string nameOBJ = path;
	nameOBJ.append(modelFileName);
	nameOBJ.append(".obj");
	Image image = { 0 };
	Model loadModel = { 0 };

	if (FileExists(const_cast<char*>(nameOBJ.c_str())) &&
		FileExists(const_cast<char*>(namePNG.c_str())))
	{
		loadModel = SetTextureToModel(LoadModel(const_cast<char*>(nameOBJ.c_str())),
			LoadTexture(const_cast<char*>(namePNG.c_str())));
	}
	else
	{
		TraceLog(LOG_ERROR, "***********************  Image  :%s missing. ***********************\n",
			const_cast<char*>(nameOBJ.c_str()));
		TraceLog(LOG_ERROR, "***********************  Image  :%s missing. ***********************\n",
			const_cast<char*>(namePNG.c_str()));
	}

	return loadModel;
}

Model GameLogic::SetTextureToModel(Model model, Texture2D texture)
{
	if (IsTextureReady(texture))
	{
		model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
	}

	return model;
}

void GameLogic::Load()
{
	//Load all the models and textures used by the Land class, including the UI.

	for (int i = 0; i < 7; i++)
	{
		std::string name = "Ground";
		std::string nameR = "GroundRadar";
		name.append(std::to_string(i + 1));
		nameR.append(std::to_string(i + 1));

		TheLand.LandParts[i].SetModelCopy(LoadModelwithTexture(name), 50.0f);
		TheLand.RadarLandParts[i].SetModelCopy(LoadModelwithTexture(nameR), 3.18f);
	}

	TheLand.SetUIBack(LoadModelwithTexture("UIBackface"));
	TheLand.SetUIHorz(LoadModelwithTexture("RadarH"));
	TheLand.SetRadarTopBottom(LoadModelwithTexture("RadarHOutline"));
	TheLand.SetStar(LoadModelwithTexture("Star"));
	//Load all the models and their textures used by Player.
	ThePlayer.SetModel(LoadModelwithTexture("Player Ship"));
	ThePlayer.SetRadarModel(LoadModelwithTexture("Player Radar"));
	ThePlayer.SetFlameModel(LoadModelwithTexture("Player Flame"));
	ThePlayer.SetShotModel(LoadModelwithTexture("Player Shot"));
	ThePlayer.SetTailModel(LoadModelwithTexture("Player Shot Tail"));
	ThePlayer.SetSmartbombModel(LoadModelwithTexture("BombIcon"));
	//Load all the models and their textures used by Lander and Mutant.
	Model shot = LoadModelwithTexture("Shot");
	LandersMutants.SetLanderModel(LoadModelwithTexture("Lander"));
	LandersMutants.SetMutantModel(LoadModelwithTexture("Mutant"));
	LandersMutants.SetShotModel(shot);
	LandersMutants.SetPersonModel(LoadModelwithTexture("Person"));
	LandersMutants.SetLanderRadarModel(LoadModelwithTexture("Lander Radar"));
	LandersMutants.SetPersonRadar(LoadModelwithTexture("Person Radar"));
	LandersMutants.SetMutantRadarModel(LoadModelwithTexture("Mutant Radar"));
	//Load all the models and their textures used by the Bomber.
	Bombers.SetBomber(LoadModelwithTexture("Bomber"));
	Bombers.SetBomb(LoadModelwithTexture("Bomb"));
	Bombers.SetBomberRadar(LoadModelwithTexture("Bomber Radar"));
	//Load all the models and their textures used by Pod and Swarmer.
	PodsSwarmers.SetPodModel(LoadModelwithTexture("Pod"));
	PodsSwarmers.SetSwarmerModel(LoadModelwithTexture("Swarmer"));
	PodsSwarmers.SetShotModel(shot);
	PodsSwarmers.SetPodRadarModel(LoadModelwithTexture("Pod Radar"));
	PodsSwarmers.SetSwarmerRadarModel(LoadModelwithTexture("Swarmer Radar"));
	// Load up cube for FX
	Explosions.SetCubeModel(LoadModelwithTexture("Cube"));

	//********* Sounds ***************
	ThePlayer.SetSounds(LoadSound("Sounds/Player Shot.wav"), LoadSound("Sounds/Player Explode.wav"),
		LoadSound("Sounds/Player Thrust.wav"), LoadSound("Sounds/Smartbomb.wav"),
		LoadSound("Sounds/Bonus.wav"));

	Sound enemyExplodeSound = LoadSound("Sounds/Enemy Explode.wav");

	LandersMutants.SetSounds(LoadSound("Sounds/Enemy Shot.wav"), enemyExplodeSound,
		LoadSound("Sounds/Mutant Shot.wav"), LoadSound("Sounds/Lander Mutate.wav"),
		LoadSound("Sounds/Landers Spawn.wav"));
	LandersMutants.SetPersonSounds(LoadSound("Sounds/Person Grabbed.wav"),
		LoadSound("Sounds/Person Dropped.wav"), LoadSound("Sounds/Person Caught.wav"),
		LoadSound("Sounds/Person Landed.wav"), LoadSound("Sounds/Person Exploded.wav"));

	Bombers.SetSounds(LoadSound("Sounds/Bomber Explode.wav"));

	PodsSwarmers.SetSounds(LoadSound("Sounds/Pod Explode.wav"), LoadSound("Sounds/Swarmer Explode.wav"),
		LoadSound("Sounds/Swarmer Shot.wav"));
}

bool GameLogic::BeginRun(Camera* camera)
{
	Score.BeginRun();
	ThePlayer.BeginRun(camera);
	ThePlayer.SetExplosion(&Explosions);
	TheLand.SetPlayer(&ThePlayer);
	LandersMutants.SetPlayer(&ThePlayer);
	LandersMutants.SetData(&Data);
	LandersMutants.SetExplosion(&Explosions);
	LandersMutants.SetScore(&Score);
	Bombers.SetPlayer(&ThePlayer);
	Bombers.SetData(&Data);
	Bombers.SetExplosion(&Explosions);
	Bombers.SetScore(&Score);
	PodsSwarmers.SetPlayer(&ThePlayer);
	PodsSwarmers.SetData(&Data);
	PodsSwarmers.SetExplosion(&Explosions);
	PodsSwarmers.SetScore(&Score);
	//BeginRun after everything else.
	TheLand.BeginRun(camera);
	LandersMutants.BeginRun(camera);
	Bombers.BeginRun(camera);
	PodsSwarmers.BeginRun(camera);
	Explosions.BeginRun(camera);

	return false;
}

void GameLogic::Input()
{
	if (State == InPlay || State == WaveStart)
	{
		ThePlayer.Input();
	}

	if (IsKeyPressed(KEY_P))
	{
		if (State == InPlay)
		{
			State = Pause;
		}
		else if (State == Pause)
		{
			State = InPlay;
		}
	}

	if (IsGamepadAvailable(0))
	{
		if (IsGamepadButtonPressed(0, 13))
		{	//Back Button is 13
			if (State == InPlay)
			{
				State = Pause;
			}
			else if (State == Pause)
			{
				State = InPlay;
			}
		}
	}

	if (State == MainMenu)
	{
		if (IsKeyPressed(KEY_N))
		{
			NewGame();
		}

		if (IsGamepadAvailable(0))
		{	//Start Button is 15

			if (IsGamepadButtonPressed(0, 15))
			{
				NewGame();
			}
		}
	}
}

void GameLogic::Update(float deltaTime)
{
	if (Score.Bonus)
	{
		ThePlayer.Bonus();
		Score.Bonus = false;
	}

	if (State == InPlay)
	{
		UpdatePlayerLand(deltaTime);
		LandersMutants.Update(deltaTime);
		Bombers.Update(deltaTime);
		PodsSwarmers.Update(deltaTime);
		Explosions.Update(deltaTime);

		if (ThePlayer.BeenHit)
		{
			PlayerWasHit();
			return;
		}

		if (ThePlayer.SmartBombFired)
		{
			SmartBombFired();
			return;
		}

		if (Data.PeopleBeGone && !LandersMutants.LandersTurnedToMutants)
		{
			LandersMutants.TheyAllDied();
			TheLand.AllThePersonManDead();
		}

		CheckEndOfLevelWave();
	}
	else if (State == PlayerHitByEnemy)
	{
		PlayerDeathTimer.Update(deltaTime);
		Explosions.Update(deltaTime);

		if (PlayerDeathTimer.Elapsed())
		{
			State = AfterPlayerHit;
		}
	}
	else if (State == AfterPlayerHit)
	{
		PlayerResetTimer.Update(deltaTime);

		if (PlayerResetTimer.Elapsed())
		{
			if (ThePlayer.GameOver)
			{
				State = MainMenu;
				return;
			}

			State = WaveStart;
			WaveStartTimer.Reset();
			ResetAfterExplode();
			ThePlayer.NewWave();
		}
	}
	else if (State == WaveStart)
	{
		WaveStartTimer.Update(deltaTime);
		UpdatePlayerLand(deltaTime);

		if (WaveStartTimer.Elapsed())
		{
			State = InPlay;
			NewWaveStart();
		}
	}
	else if (State == NewWave)
	{
		NewWaveTimer.Update(deltaTime);

		if (NewWaveTimer.Elapsed())
		{
			State = WaveStart;
			WaveStartTimer.Reset();
			ThePlayer.NewWave();
		}
	}
	else
	{
		TheLand.Update(deltaTime);
	}
}

void GameLogic::Draw3D()
{
	if (State != NewWave)
	{
		ThePlayer.Draw();
		TheLand.Draw();
		Explosions.Draw();

		if (State == InPlay || State == PlayerHitByEnemy)
		{
			LandersMutants.Draw();
			Bombers.Draw();
			PodsSwarmers.Draw();
		}
	}
}

void GameLogic::Draw2D()
{
	if (State == NewWave)
	{
		DrawText("Wave Completed", (int)((GetScreenWidth() * 0.5f) - ((30 * 15) * 0.25f)),
			(int)(GetScreenHeight() * 0.5f), 30, GRAY);
	}
	else if (State == Pause)
	{
		DrawText("Paused", (int)((GetScreenWidth() * 0.5f) - ((40 * 7) * 0.25f)),
			(int)(GetScreenHeight() * 0.5f), 40, GRAY);
	}
	else if (State == WaveStart)
	{
		DrawText("Get Ready", (int)((GetScreenWidth() * 0.5f) - ((40 * 10) * 0.25f)),
			(int)(GetScreenHeight() * 0.5f), 40, GRAY);
	}
	else if (State == MainMenu)
	{
		DrawText("Press N to start", (int)((GetScreenWidth() * 0.5f) - ((30 * 17) * 0.25f)),
			(int)(GetScreenHeight() * 0.5f), 30, GRAY);

		Score.Draw();
	}
	else
	{
		Score.Draw();
	}
}

void GameLogic::PlayerHit()
{
}

void GameLogic::UpdatePlayerLand(float deltaTime)
{
	ThePlayer.Update(deltaTime);
	TheLand.Update(deltaTime);
}

void GameLogic::CheckEndOfWave()
{
}

void GameLogic::CheckEndOfLevelWave()
{
	if (Data.LandersMutantsBeGone && Data.PodsSwarmersBeGone && Data.BombersBeGone)
	{
		State = NewWave;
		Data.Wave++;
		NewWaveTimer.Reset();
		ThePlayer.Reset();
		Explosions.Reset();
		LandersMutants.EndOfLevelWave();
		LandersMutants.NewLevelWave();
		Bombers.NewWave();
		PodsSwarmers.NewWave();
		TheLand.NewLevel();

		if (Data.Wave > 0)
		{

		}
	}
}

void GameLogic::NewWaveStart()
{
	LandersMutants.StartWave();
}

void GameLogic::SmartBombFired()
{
	ThePlayer.SmartBombFired = false;
	float windowWidth = GetScreenWidth() / 1.4f;
	float minX = 0;
	float maxX = 0;

	minX = ThePlayer.X() - windowWidth;
	maxX = ThePlayer.X() + windowWidth;

	LandersMutants.Smartbomb(minX, maxX);
	Bombers.Smartbomb(minX, maxX);
	PodsSwarmers.Smartbomb(minX, maxX);

	float gameEdge = GetScreenWidth() * 3.5f;

	if (ThePlayer.X() > (gameEdge - windowWidth))
	{
		minX -= (gameEdge * 2);
		maxX -= (gameEdge * 2);

		LandersMutants.Smartbomb(minX, maxX);
		Bombers.Smartbomb(minX, maxX);
		PodsSwarmers.Smartbomb(minX, maxX);
	}
	else if (ThePlayer.X() < (-gameEdge + windowWidth))
	{
		minX += (gameEdge * 2);
		maxX += (gameEdge * 2);

		LandersMutants.Smartbomb(minX, maxX);
		Bombers.Smartbomb(minX, maxX);
		PodsSwarmers.Smartbomb(minX, maxX);
	}
}

void GameLogic::NewGame()
{
	State = WaveStart;
	Data.Wave = 0;
	ThePlayer.NewGame();
	LandersMutants.NewGame();
	Score.ClearScore();
}

void GameLogic::ResetAfterExplode()
{
	PlayerResetTimer.Reset(0.666f);
	ThePlayer.Reset();
	LandersMutants.PlayerHitReset();
	Bombers.Reset();
	PodsSwarmers.Reset();
	Explosions.Reset();
}

void GameLogic::PlayerWasHit()
{
	State = PlayerHitByEnemy;
	PlayerDeathTimer.Reset(5.666f);
}
