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
	SetWindowTitle("Defender Alpha 01.00");
	ThePlayer.Initialize();
	ControlLanderMutant.Initialize();
	TheLand.Initialize();
	Bombers.Initialize();
	Swarmers.Initialize();
	NewWaveTimer.Set(1.5f);

	return false;
}

Model GameLogic::LoadModelwithTexture(string modelFileName)
{
	string path = "models/";

	string namePNG = path;
	namePNG.append(modelFileName);
	namePNG.append(".png");

	string nameOBJ = path;
	nameOBJ.append(modelFileName);
	nameOBJ.append(".obj");
	Image image = { 0 };
	Model loadModel = { 0 };

	if (FileExists(const_cast<char*>(namePNG.c_str())))
	{
		image = LoadImage(const_cast<char*>(namePNG.c_str()));
	}
	else
	{
		fprintf(stderr, "**********************************************************************************************\n");
		fprintf(stderr, "*****************  Image  :%s missing. *****************\n", const_cast<char*>(namePNG.c_str()));
		fprintf(stderr, "**********************************************************************************************\n");
	}

	if (FileExists(const_cast<char*>(nameOBJ.c_str())))
	{
		loadModel = UploadTextureToModel(LoadModel(const_cast<char*>(nameOBJ.c_str())), LoadTextureFromImage(image));
		UnloadImage(image);
	}
	else
	{
		fprintf(stderr, "**********************************************************************************************\n");
		fprintf(stderr, "******************  Model  :%s missing. ****************\n", const_cast<char*>(nameOBJ.c_str()));
		fprintf(stderr, "**********************************************************************************************\n");
	}


	return loadModel;
}

Model GameLogic::UploadTextureToModel(Model model, Texture2D texture)
{
	Model buildModel = { 0 };

	if (IsTextureReady(texture))
	{
		buildModel = model;
		buildModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
	}

	return buildModel;
}

void GameLogic::Load()
{
	//Load all the models and textures used by the Land class, including the UI.

	for (int i = 0; i < 7; i++)
	{
		string name = "Ground";
		string nameR = "GroundRadar";
		name.append(to_string(i + 1));
		nameR.append(to_string(i + 1));

		TheLand.LandParts[i]->SetModel(LoadModelwithTexture(name));
		TheLand.RadarLandParts[i]->SetModel(LoadModelwithTexture(nameR));
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
	//Load all the models and their textures used by Lander and Mutant.
	Model shot = LoadModelwithTexture("Shot");
	ControlLanderMutant.SetLanderModel(LoadModelwithTexture("Lander"));
	ControlLanderMutant.SetMutantModel(LoadModelwithTexture("Mutant"));
	ControlLanderMutant.SetShotModel(shot);
	ControlLanderMutant.SetPersonModel(LoadModelwithTexture("Person"));
	ControlLanderMutant.SetLanderRadarModel(LoadModelwithTexture("Lander Radar"));
	ControlLanderMutant.SetPersonRadar(LoadModelwithTexture("Person Radar"));
	ControlLanderMutant.SetMutantRadarModel(LoadModelwithTexture("Mutant Radar"));
	//Load all the models and their textures used by the Bomber.
	Bombers.SetBomber(LoadModelwithTexture("Bomber"));
	Bombers.SetBomb(LoadModelwithTexture("Bomb"));
	Bombers.SetBomberRadar(LoadModelwithTexture("Bomber Radar"));
	//Load all the models and their textures used by Pod and Swarmer.
	Swarmers.SetPodModel(LoadModelwithTexture("Pod"));
	Swarmers.SetSwarmerModel(LoadModelwithTexture("Swarmer"));
	Swarmers.SetShotModel(shot);
	Swarmers.SetPodRadarModel(LoadModelwithTexture("Pod Radar"));
	Swarmers.SetSwarmerRadarModel(LoadModelwithTexture("Swarmer Radar"));
}

bool GameLogic::BeginRun(Camera* camera)
{
	TheCamera = camera;
	ThePlayer.BeginRun(camera);
	TheLand.SetPlayer(&ThePlayer);
	ControlLanderMutant.SetPlayer(&ThePlayer);
	ControlLanderMutant.SetData(&Data);
	Bombers.SetPlayer(&ThePlayer);
	Swarmers.SetPlayer(&ThePlayer);
	TheLand.BeginRun(camera);
	ControlLanderMutant.BeginRun(camera);
	Bombers.BeginRun(camera);
	Swarmers.BeginRun(camera);

	return false;
}

void GameLogic::Input()
{
	if (!NewWave)
		ThePlayer.Input();

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
}

void GameLogic::Update(float deltaTime)
{
	if (State == InPlay)
	{
		NewWaveTimer.Update(deltaTime);
		ThePlayer.Update(deltaTime);
		TheLand.Update(deltaTime);
		ControlLanderMutant.Update(deltaTime);
		Bombers.Update(deltaTime);
		Swarmers.Update(deltaTime);
		CheckEndOfWave();

		if (ThePlayer.BeenHit)
		{
			PlayerWasHit();
		}
	}
	else if (State == PlayerHit)
	{
		PlayerResetTimer.Update(deltaTime);
		ThePlayer.Update(deltaTime);
		TheLand.Update(deltaTime);

		if (PlayerResetTimer.Elapsed())
		{
			State = InPlay;
		}
	}
}

void GameLogic::Draw3D()
{
	if (!NewWave)
	{
		ThePlayer.Draw();
		TheLand.Draw();

		if (State != PlayerHit)
		{
			ControlLanderMutant.Draw();
			Bombers.Draw();
			Swarmers.Draw();
		}
	}
}

void GameLogic::Draw2D()
{
	if (NewWave)
	{
		DrawText("Wave Completed", (int)((GetScreenWidth() * 0.5f) - ((30 * 15) * 0.25f)),
			(int)(GetScreenHeight() * 0.5f), 30, GRAY);
	}
	else
	{
		Score.Draw();
	}
}

void GameLogic::CheckEndOfWave()
{
	if (Data.LandersMutantsBeGone)
	{
		Data.Wave++;
		ControlLanderMutant.NewLevelWave();
		ThePlayer.Reset();
		NewWave = true;
		NewWaveTimer.Reset();
	}

	if (NewWave)
	{
		if (NewWaveTimer.Elapsed())
		{
			NewWave = false;
		}
	}
}

void GameLogic::PlayerWasHit()
{
	State = PlayerHit;
	PlayerResetTimer.Reset(1.3f);
	ThePlayer.Reset();
	ControlLanderMutant.PlayerHitReset();
}
