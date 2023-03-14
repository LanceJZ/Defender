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
	SetWindowTitle("Defender Pre-Alpha 00.10");
	ThePlayer->Initialize();
	ControlLanderMutant->Initialize();
	TheLand->Initialize();
	Bombers->Initialize();
	Swarmers->Initialize();

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

	Image image = LoadImage(const_cast<char*>(namePNG.c_str()));
	Model loadModel = UploadTextureToModel(LoadModel(const_cast<char*>(nameOBJ.c_str())), LoadTextureFromImage(image));
	UnloadImage(image);

	return loadModel;
}

Model GameLogic::UploadTextureToModel(Model model, Texture2D texture)
{
	Model buildModel;
	buildModel = model;
	buildModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

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

		TheLand->LandParts[i]->TheModel = LoadModelwithTexture(name);
		TheLand->RadarLandParts[i]->TheModel = LoadModelwithTexture(nameR);
	}

	TheLand->SetUIBack(LoadModelwithTexture("UIBackface"));
	TheLand->SetRadarHorz(LoadModelwithTexture("RadarH"));
	TheLand->SetStar(LoadModelwithTexture("Star"));
	//Load all the models and their textures used by Player.
	ThePlayer->SetModel(LoadModelwithTexture("Player Ship"));
	ThePlayer->SetRadarModel(LoadModelwithTexture("Player Radar"));
	ThePlayer->SetFlameModel(LoadModelwithTexture("Player Flame"));
	ThePlayer->SetShotModel(LoadModelwithTexture("Player Shot"));
	ThePlayer->SetTailModel(LoadModelwithTexture("Player Shot Tail"));
	//Load all the models and their textures used by Lander and Mutant.
	Model shot = LoadModelwithTexture("Shot");
	ControlLanderMutant->SetLanderModel(LoadModelwithTexture("Lander"));
	ControlLanderMutant->SetMutantModel(LoadModelwithTexture("Mutant"));
	ControlLanderMutant->SetShotModel(shot);
	ControlLanderMutant->SetPersonModel(LoadModelwithTexture("Person"));
	ControlLanderMutant->SetLanderRadarModel(LoadModelwithTexture("Lander Radar"));
	ControlLanderMutant->SetPersonRadar(LoadModelwithTexture("Person Radar"));
	ControlLanderMutant->SetMutantRadarModel(LoadModelwithTexture("Mutant Radar"));
	//Load all the models and their textures used by the Bomber.
	Bombers->SetBomber(LoadModelwithTexture("Bomber"));
	Bombers->SetBomb(LoadModelwithTexture("Bomb"));
	Bombers->SetBomberRadar(LoadModelwithTexture("Bomber Radar"));
	//Load all the models and their textures used by Pod and Swarmer.
	Swarmers->SetPodModel(LoadModelwithTexture("Pod"));
	Swarmers->SetSwarmerModel(LoadModelwithTexture("Swarmer"));
	Swarmers->SetShotModel(shot);
	Swarmers->SetPodRadarModel(LoadModelwithTexture("Pod Radar"));
	Swarmers->SetSwarmerRadarModel(LoadModelwithTexture("Swarmer Radar"));
}

bool GameLogic::BeginRun(Camera* camera)
{
	TheCamera = camera;
	ThePlayer->BeginRun(camera);
	TheLand->SetPlayer(ThePlayer);
	ControlLanderMutant->SetPlayer(ThePlayer);
	Bombers->SetPlayer(ThePlayer);
	Swarmers->SetPlayer(ThePlayer);
	TheLand->BeginRun(camera);
	ControlLanderMutant->BeginRun(camera);
	Bombers->BeginRun(camera);
	Swarmers->BeginRun(camera);

	return false;
}

void GameLogic::Input()
{
	ThePlayer->Input();

	if (IsKeyPressed(KEY_P))
		Pause = !Pause;
}

void GameLogic::Update(float deltaTime)
{
	if (!Pause)
	{
		ThePlayer->Update(deltaTime);
		TheLand->Update(deltaTime);
		ControlLanderMutant->Update(deltaTime);
		Bombers->Update(deltaTime);
		Swarmers->Update(deltaTime);
	}
}

void GameLogic::Draw3D()
{
	ThePlayer->Draw();
	TheLand->Draw();
	ControlLanderMutant->Draw();
	Bombers->Draw();
	Swarmers->Draw();
}

void GameLogic::Draw2D()
{

}
